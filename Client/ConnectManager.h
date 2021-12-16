#pragma once

#include"config.h"

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
	int GetSocket() { return m_socket; }
	struct sockaddr_in GetAddr() { return  m_sock_addr; }
	void SetSockAddrAndPort(LPWSTR** s);

private:

	ConnectManager()
	{
		m_socket = socket(AF_INET, SOCK_DGRAM, 0);
		mut_pack_in = CreateMutex(NULL, FALSE, "Pack_in");
		mut_pack_out = CreateMutex(NULL, FALSE, "Pack_out");
	}
	~ConnectManager()
	{
		CloseHandle(mut_pack_in);
		CloseHandle(mut_pack_out);
		closesocket(m_socket);
	}

	static DWORD* wrapper_connection_thread() { ConnectManager::GetInstance()->connection_thread(); return nullptr; }
	void connection_thread();

	PackOut m_packet_out;

	sockaddr_in m_sock_addr = {};
	int m_socket;
	HANDLE mut_pack_in;
	HANDLE mut_pack_out;
};
