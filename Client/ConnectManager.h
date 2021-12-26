#pragma once
#include <string>
#include <winsock.h>
#include "config.h"


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
	void ConnectThread();
	int ConnectionStatus();
	int GetSocket() { return m_socket; }
	struct sockaddr_in GetAddr() { return  m_sock_addr; }
	void SetSockAddrAndPort(std::string s);

private:
	ConnectManager()
	{
		m_connect_stat = DISCONNECTED;
		m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	}

	~ConnectManager()
	{
		closesocket(m_socket);
	}

	static DWORD* wrapper_connection_thread() { ConnectManager::GetInstance()->connection_thread(); return nullptr; }

	int connection_thread();

	int m_connection_delay = 0;
	sockaddr_in m_sock_addr = {};
	int m_socket;
	int m_connect_stat;
};
