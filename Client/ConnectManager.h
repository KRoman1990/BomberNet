#pragma once
#include <utility>
#include <winsock.h>
#include "config.h"
#include "game_functions.h"
#include "ResMng.h"
#include "Player.h"
#include "Wall.h"
#include "Crate.h"
#include "Burn.h"
#include "Bomb.h"
#include "Enemy.h"
#include "Upgrade_Shield.h"
#include "Upgrade_ManyBombs.h"
#include "BombRange.h"

struct PackOut
{
	int map[LINE_LENGTH * COLUMNS];
	int id[MAX_PLAYERS];
};

class ConnectManager
{
public:
	static ConnectManager* GetInstance();
	void SendBombMsg(int coordinates);
	void SendDeathMsg(int id_recv);
	void SetPackIn();
	PackOut GetPackOut() { return m_packet_out; }
	void ConnectInit();
	int ConnectionStatus();
	int GetSocket() { return m_socket; }
	struct sockaddr_in GetAddr() { return  m_sock_addr; }
	void SetSockAddrAndPort(string s);

private:

	ConnectManager()
	{
		m_socket = socket(AF_INET, SOCK_DGRAM, 0);
		mut_pack_in = CreateMutex(NULL, FALSE, "Pack_in");
	}
	~ConnectManager()
	{
		CloseHandle(mut_pack_in);
		CloseHandle(mut_pack_out);
		closesocket(m_socket);
	}

	static DWORD* wrapper_connection_thread() { ConnectManager::GetInstance()->connection_thread(); return nullptr; }
	int connection_thread();
	PackOut m_packet_out;
	int connection_delay = 0;
	sockaddr_in m_sock_addr = {};
	int m_socket;
	int connect_stat;
	HANDLE mut_pack_in;
	HANDLE mut_pack_out;
};
