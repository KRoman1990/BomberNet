#include "ConnectManager.h"
#include <cassert>

#include "GameFuncs.h"
#include "ResMng.h"
#include "Resources.h"


//static
ConnectManager* ConnectManager::GetInstance()
{
	static ConnectManager* instance = nullptr;
	if (!instance)
	{
		instance = new ConnectManager();
	}
	return instance;
}

int ConnectManager::ConnectionStatus()
{
	return m_connect_stat;
}

int ConnectManager::connection_thread()
{
	int key = MAGIC_CONNECT_KEY;
	int id;
	auto addr = GetAddr();

	connect(m_socket, (sockaddr*)&addr, sizeof(GetAddr()));
	send(m_socket, (char*)&key, sizeof(int), 0);
	while (recv(m_socket, (char*)&id, sizeof(int), 0) <= 0);

	m_connect_stat = CONNECTED;
	m_connection_delay = 0;
	auto pg = Player::GetInstance();
	pg->SetId(id);

	while (1)
	{
		char buffer[1024] = {};
		while (recv(m_socket, buffer, sizeof(PackOut), 0) <= 0 && m_connection_delay <= 10000)
		{
			m_connection_delay++;
			if (m_connection_delay > 10000)
			{
				m_connect_stat = DISCONNECTED;
			}
		}
		m_connection_delay = 0;
		PackOut &packet_out = *(PackOut *)buffer;

		EnterCriticalSection(GameFuncs::GetInstance()->GetCriticalSection());
		GameFuncs::GetInstance()->ReleaseObjectList();
		for (int i = 0; i < LINE_LENGTH * COLUMNS; i++)
		{
			int player_point = packet_out.map[i];
			if (player_point & BLOCK_WALL)
			{
				GameFuncs::GetInstance()->AddObjectList(new Wall(i));
			}
			if (player_point & BLOCK_UPGRADE_SHIELD && !((
				player_point & BLOCK_PLAYER1 ||
				player_point & BLOCK_PLAYER2 ||
				player_point & BLOCK_PLAYER3 ||
				player_point & BLOCK_PLAYER4)))
			{
				GameFuncs::GetInstance()->AddObjectList(new Shield(i));
			}
			if (player_point & BLOCK_UPGRADE_MANYBOMBS && !((
				player_point & BLOCK_PLAYER1 ||
				player_point & BLOCK_PLAYER2 ||
				player_point & BLOCK_PLAYER3 ||
				player_point & BLOCK_PLAYER4)))
			{
				GameFuncs::GetInstance()->AddObjectList(new ManyBombs(i));
			}
			if (player_point & BLOCK_UPGRADE_BOMBRANGE && !((
				player_point & BLOCK_PLAYER1 ||
				player_point & BLOCK_PLAYER2 ||
				player_point & BLOCK_PLAYER3 ||
				player_point & BLOCK_PLAYER4)))
			{
				GameFuncs::GetInstance()->AddObjectList(new BombRange(i));
			}
			if (player_point & BLOCK_CRATE)
			{
				GameFuncs::GetInstance()->AddObjectList(new Crate(i));
			}
			if (player_point & BLOCK_BOMB_1)
			{
				GameFuncs::GetInstance()->AddObjectList(new Bomb(i, RES_SPRITE_BOMB_1));
			}
			if (player_point & BLOCK_BOMB_2)
			{
				GameFuncs::GetInstance()->AddObjectList(new Bomb(i, RES_SPRITE_BOMB_2));
			}
			if (player_point & BLOCK_BOMB_3)
			{
				GameFuncs::GetInstance()->AddObjectList(new Bomb(i, RES_SPRITE_BOMB_3));
			}
			if (player_point & BLOCK_BURNING_1)
			{
				GameFuncs::GetInstance()->AddObjectList(new Burn(i));
			}
			if (player_point & BLOCK_PLAYER1 ||
				player_point & BLOCK_PLAYER2 ||
				player_point & BLOCK_PLAYER3 ||
				player_point & BLOCK_PLAYER4)
			{

				if (player_point & BLOCK_BOMB_1)
				{
					player_point -= BLOCK_BOMB_1;
				}
				if (player_point & BLOCK_BOMB_2)
				{
					player_point -= BLOCK_BOMB_2;
				}
				if (player_point & BLOCK_BOMB_3)
				{
					player_point -= BLOCK_BOMB_3;
				}
				if (player_point & BLOCK_UPGRADE_SHIELD)
				{
					player_point -= BLOCK_UPGRADE_SHIELD;
				}
				if (pg->GetId() == player_point)
				{
					pg->SetCoord(i);
					GameFuncs::GetInstance()->AddObjectList(Player::GetInstance());
				}
				else
				{
					GameFuncs::GetInstance()->AddObjectList(new Enemy(i, (player_point)));
				}
				if (player_point & BLOCK_UPGRADE_SHIELD && (
					player_point & BLOCK_PLAYER1 ||
					player_point & BLOCK_PLAYER2 ||
					player_point & BLOCK_PLAYER3 ||
					player_point & BLOCK_PLAYER4))
				{
					GameFuncs::GetInstance()->AddObjectList(new ShieldOnPlayer(i));
				}
			}
		}
		LeaveCriticalSection(GameFuncs::GetInstance()->GetCriticalSection());

		pg->SendPack(PACKET_HEARTBEAT);
	}
}

void ConnectManager::ConnectThread()
{
	unsigned long threadId;
	void* thread;
	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)wrapper_connection_thread, NULL, 0, &threadId);
}

void ConnectManager::SetSockAddrAndPort(std::string s)
{
	// addr parsing
	m_sock_addr.sin_family = AF_INET;
	m_sock_addr.sin_addr.s_addr = inet_addr(s.c_str());

	// port parsing
	m_sock_addr.sin_port = htons(CONNECT_PORT);
}
