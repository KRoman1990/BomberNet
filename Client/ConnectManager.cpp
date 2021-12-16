#include <utility>
#include <winsock.h>
#include "config.h"
#include "ResMng.h"
#include "ConnectManager.h"
#include "Player.h"
#include "Wall.h"
#include "Crate.h"
#include "Burn.h"
#include "Bomb.h"
#include "Enemy.h"
#include "Upgrade_Shield.h"
#include "Upgrade_ManyBombs.h"

extern std::list<Object*> gObjectList;
extern CRITICAL_SECTION CriticalSection;

//static
ConnectManager* ConnectManager::GetInstance()
{
	static ConnectManager* instance;
	if (!instance)
	{
		instance = new ConnectManager();
	}
	return instance;
}


void ConnectManager::connection_thread()
{
	int key = 123;
	char addr_pack[1024] = {};
	int id;
	auto addr = GetAddr();
	connect(GetSocket(), (sockaddr*)&addr, sizeof(GetAddr()));
	send(GetSocket(), (char*)&key, sizeof(int), 0);
	while (recv(GetSocket(), (char*)&id, sizeof(int), 0) <= 0);
	auto pg = Player::GetInstance();
	pg->SetId(id);
	while (recv(GetSocket(), addr_pack, sizeof(m_packet_out), 0) <= 0);
	memcpy(&m_packet_out, addr_pack, sizeof(m_packet_out));
	memset(addr_pack, 0, sizeof(addr_pack));
	while (1)
	{/*
		static unsigned long g_last_time = GetTickCount();
		if (GetTickCount() - g_last_time < 7)
		{
			continue;
		}
		g_last_time = GetTickCount();*/

		pg->SendPack(PACKET_HEARTBEAT);
		while (recv(GetSocket(), addr_pack, sizeof(m_packet_out), 0) <= 0);
		memcpy(&m_packet_out, addr_pack, sizeof(m_packet_out));

		EnterCriticalSection(&CriticalSection);
		for (auto& o : gObjectList)
		{
			if (o != Player::GetInstance())
			{
				delete(o);
			}
		}
		gObjectList.clear();
		for (int i = 0; i < LINE_LENGTH * COLUMNS; i++)
		{
			int point = m_packet_out.map[i];
			if (m_packet_out.map[i] & BLOCK_PLAYER1 ||
				m_packet_out.map[i] & BLOCK_PLAYER2 ||
				m_packet_out.map[i] & BLOCK_PLAYER3 ||
				m_packet_out.map[i] & BLOCK_PLAYER4)
			{
				
				if (m_packet_out.map[i] & BLOCK_BOMB_1)
				{
					point -= BLOCK_BOMB_1;
				}
				if (m_packet_out.map[i] & BLOCK_BOMB_2)
				{
					point -= BLOCK_BOMB_2;
				}
				if (m_packet_out.map[i] & BLOCK_BOMB_3)
				{
					point -= BLOCK_BOMB_3;
				}
				if (pg->GetId() == point)
				{
					pg->SetCoord(i);
					gObjectList.push_back(Player::GetInstance());
				}
				else
				{
					gObjectList.push_back(new Enemy(i, (point)));
				}
			}
			if (m_packet_out.map[i] & BLOCK_WALL)
			{
				gObjectList.push_back(new Wall(i));
			}
			if (m_packet_out.map[i] & BLOCK_UPGRADE1 && !((
				m_packet_out.map[i] & BLOCK_PLAYER1 ||
				m_packet_out.map[i] & BLOCK_PLAYER2 ||
				m_packet_out.map[i] & BLOCK_PLAYER3 ||
				m_packet_out.map[i] & BLOCK_PLAYER4)))
			{
				gObjectList.push_back(new Shield(i));
			}
			if (m_packet_out.map[i] & BLOCK_UPGRADE2 && !((
				m_packet_out.map[i] & BLOCK_PLAYER1 ||
				m_packet_out.map[i] & BLOCK_PLAYER2 ||
				m_packet_out.map[i] & BLOCK_PLAYER3 ||
				m_packet_out.map[i] & BLOCK_PLAYER4)))
			{
				gObjectList.push_back(new ManyBombs(i));
			}
			if (m_packet_out.map[i] & BLOCK_CRATE)
			{
				gObjectList.push_back(new Crate(i));
			}
			if (m_packet_out.map[i] & BLOCK_BOMB_1)
			{
				gObjectList.push_back(new Bomb(i, RES_SPRITE_BOMB_1));
			}
			if (m_packet_out.map[i] & BLOCK_BOMB_2)
			{
				gObjectList.push_back(new Bomb(i, RES_SPRITE_BOMB_2));
			}
			if (m_packet_out.map[i] & BLOCK_BOMB_3)
			{
				gObjectList.push_back(new Bomb(i, RES_SPRITE_BOMB_3));
			}
			if (m_packet_out.map[i] & BLOCK_BURNING_1)
			{
				gObjectList.push_back(new Burn(i));
			}
		}
		LeaveCriticalSection(&CriticalSection);
	}
}

void ConnectManager::ConnectInit()
{
	unsigned long threadId;
	void* thread;
	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)wrapper_connection_thread, NULL, 0, &threadId);
}

void ConnectManager::SetSockAddrAndPort(LPWSTR** s)
{
	LPWSTR* sz_arglist = *s;
	char argv[20] = {};
	size_t len = wcstombs(argv, sz_arglist[1], wcslen(sz_arglist[1]));

	// addr parsing
	m_sock_addr.sin_family = AF_INET;
	m_sock_addr.sin_addr.s_addr = inet_addr(argv);

	// port parsing
	memset(argv, 0, 20);
	len = wcstombs(argv, sz_arglist[2], wcslen(sz_arglist[2]));
	m_sock_addr.sin_port = htons((u_short)atoi(argv));
}
