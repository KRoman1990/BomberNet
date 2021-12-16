#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include <string>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "config.h"
#pragma comment(lib,"libpthread-static.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

int map_1[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				 1, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2048, 1,
				 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
				 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
				 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
				 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
				 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
				 1, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2048, 1,
				 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

struct bomb
{
	int coordinates;
	int countdown;
	int id;
};
struct pack
{
	int map[LINE_LENGTH * COLUMNS];
	int id[4];
};
struct message
{
	int first;
	int second;
};
struct player
{
	int speed;
	std::map<std::string, bool> upgrades;
	int bombs = 1;
	int bombs_max = 1;
};
std::map<int, player> players;
struct bomb bombs[20];

struct pack packet = {};


LPTHREAD_START_ROUTINE bomb_counter()
{
	int bomb_y_plus, bomb_x_plus, bomb_y_minus, bomb_x_minus, player_hit;
	while (1)
	{
		for (int f = 0; f < 20; f++)
		{
			bombs[f].countdown--;
			if (bombs[f].countdown < 130)
			{
				packet.map[bombs[f].coordinates] = BLOCK_BOMB_2;
			}
			if (bombs[f].countdown < 60)
			{
				packet.map[bombs[f].coordinates] = BLOCK_BOMB_3;
			}
			if ((bombs[f].coordinates != -1 && bombs[f].countdown == 0) || packet.map[bombs[f].coordinates] == BLOCK_BURNING_1)
			{
				packet.map[bombs[f].coordinates] = BLOCK_EMPTY;
				bomb_y_plus = bombs[f].coordinates;
				bomb_x_plus = bombs[f].coordinates;
				bomb_y_minus = bombs[f].coordinates;
				bomb_x_minus = bombs[f].coordinates;
				bombs[f].coordinates = BLOCK_NULL;
				while (1)
				{
					std::srand(GetTickCount());
					int chance;
					if (bomb_y_plus != BLOCK_NULL)
					{
						switch (packet.map[bomb_y_plus])
						{
						case BLOCK_WALL:
							bomb_y_plus = BLOCK_NULL;
							break;
						case BLOCK_CRATE:
							packet.map[bomb_y_plus] = BLOCK_BURNING_1;
							std::srand(GetTickCount());
							chance = std::rand() % 10;
							if (chance < 7)
							{
								packet.map[bomb_y_plus] = BLOCK_UPGRADE1;
							}
							if (chance < 5)
							{
								packet.map[bomb_y_plus] = BLOCK_UPGRADE2;
							}
							bomb_y_plus = BLOCK_NULL;
							break;
						case BLOCK_PLAYER1:
						case BLOCK_PLAYER2:
						case BLOCK_PLAYER3:
						case BLOCK_PLAYER4:
							if (players[packet.map[bomb_y_plus]].upgrades["shield"])
							{
								players[packet.map[bomb_y_plus]].upgrades["shield"] = FALSE;
								bomb_y_plus = BLOCK_NULL;
								break;
							}
							else
							{
								packet.map[bomb_y_plus] = BLOCK_BURNING_1;
								bomb_y_plus -= LINE_LENGTH;
								break;
							}
						default:
							packet.map[bomb_y_plus] = BLOCK_BURNING_1;
							bomb_y_plus -= LINE_LENGTH;
							break;
						}
					}
					if (bomb_x_plus != BLOCK_NULL)
					{
						switch (packet.map[bomb_x_plus])
						{
						case BLOCK_WALL:
							bomb_x_plus = BLOCK_NULL;
							break;
						case BLOCK_CRATE:
							packet.map[bomb_x_plus] = BLOCK_BURNING_1;
							std::srand(GetTickCount());
							chance = std::rand() % 10;
							if (chance < 7)
							{
								packet.map[bomb_x_plus] = BLOCK_UPGRADE1;
							}
							if (chance < 5)
							{
								packet.map[bomb_x_plus] = BLOCK_UPGRADE2;
							}
							bomb_x_plus = BLOCK_NULL;
							break;
						case BLOCK_PLAYER1:
						case BLOCK_PLAYER2:
						case BLOCK_PLAYER3:
						case BLOCK_PLAYER4:
							if (players[packet.map[bomb_x_plus]].upgrades["shield"])
							{
								players[packet.map[bomb_x_plus]].upgrades["shield"] = FALSE;
								bomb_x_plus = BLOCK_NULL;
								break;
							}
							else
							{
								packet.map[bomb_x_plus] = BLOCK_BURNING_1;
								bomb_x_plus += 1;
								break;
							}
						default:
							packet.map[bomb_x_plus] = BLOCK_BURNING_1;
							bomb_x_plus++;
							break;
						}
					}
					if (bomb_y_minus != BLOCK_NULL)
					{
						switch (packet.map[bomb_y_minus])
						{
						case BLOCK_WALL:
							bomb_y_minus = BLOCK_NULL;
							break;
						case BLOCK_CRATE:
							packet.map[bomb_y_minus] = BLOCK_BURNING_1;
							std::srand(GetTickCount());
							chance = std::rand() % 10;
							if (chance < 7)
							{
								packet.map[bomb_y_minus] = BLOCK_UPGRADE1;
							}
							if (chance < 5)
							{
								packet.map[bomb_y_minus] = BLOCK_UPGRADE2;
							}
							bomb_y_minus = BLOCK_NULL;
							break;
						case BLOCK_PLAYER1:
						case BLOCK_PLAYER2:
						case BLOCK_PLAYER3:
						case BLOCK_PLAYER4:
							if (players[packet.map[bomb_y_minus]].upgrades["shield"])
							{
								players[packet.map[bomb_y_minus]].upgrades["shield"] = FALSE;
								bomb_y_minus = BLOCK_NULL;
								break;
							}
							else
							{
								packet.map[bomb_y_minus] = BLOCK_BURNING_1;
								bomb_y_minus -= LINE_LENGTH;
								break;
							}
						default:
							packet.map[bomb_y_minus] = BLOCK_BURNING_1;
							bomb_y_minus += LINE_LENGTH;
							break;
						}
					}
					if (bomb_x_minus != BLOCK_NULL)
					{
						switch (packet.map[bomb_x_minus])
						{
						case BLOCK_WALL:
							bomb_x_minus = BLOCK_NULL;
							break;
						case BLOCK_CRATE:
							packet.map[bomb_x_minus] = BLOCK_BURNING_1;
							std::srand(GetTickCount());
							chance = std::rand() % 10;
							if (chance < 7)
							{
								packet.map[bomb_x_minus] = BLOCK_UPGRADE1;
							}
							if (chance < 5)
							{
								packet.map[bomb_x_minus] = BLOCK_UPGRADE2;
							}
							bomb_x_minus = BLOCK_NULL;
							break;
						case BLOCK_PLAYER1:
						case BLOCK_PLAYER2:
						case BLOCK_PLAYER3:
						case BLOCK_PLAYER4:
							if (players[packet.map[bomb_x_minus]].upgrades["shield"])
							{
								players[packet.map[bomb_x_minus]].upgrades["shield"] = FALSE;
								bomb_x_minus = BLOCK_NULL;
								break;
							}
							else
							{
								packet.map[bomb_x_minus] = BLOCK_BURNING_1;
								bomb_x_minus -= LINE_LENGTH;
								break;
							}
						default:
							packet.map[bomb_x_minus] = BLOCK_BURNING_1;
							bomb_x_minus--;
							break;
						}
					}
					if (bomb_y_plus == BLOCK_NULL && bomb_x_plus == BLOCK_NULL && bomb_y_minus == BLOCK_NULL && bomb_x_minus == BLOCK_NULL)
					{
						if (players[bombs[f].id].bombs == 0)
						{
							players[bombs[f].id].bombs = players[bombs[f].id].bombs_max;
						}
						for (int m = 0; m < 2; m++)
						{
							Sleep(250);
							for (int i = 0; i < LINE_LENGTH; i++)
							{
								for (int j = 0; j < COLUMNS; j++)
								{
									if (packet.map[j + i * LINE_LENGTH] == BLOCK_BURNING_1)
									{
										packet.map[j + i * LINE_LENGTH] = BLOCK_EMPTY;
									}
								}
							}
						}
						break;
					}
				}
			}
			if (bombs[f].coordinates == -1)
			{
				bombs[f].countdown = 0;
			}
		}
		Sleep(1);
	}
}

int main()
{
#ifdef _WIN32
	static WSADATA wsaData;
	int wsaerr = WSAStartup(MAKEWORD(2, 0), &wsaData);
	(void)wsaData;
	if (wsaerr != 0)
	{
		exit(-1);
	}
	(void)wsaerr;
#endif
	unsigned long threadId;
	void* thread;
	int sockServ;
	struct sockaddr_in addrServ = {};
	struct sockaddr_in addrClient;
	int client_address_len = 0;
	int bytes_read;
	int player_amt = 1;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(7689);
	addrServ.sin_addr.s_addr = inet_addr("192.168.1.48");
	sockServ = socket(AF_INET, SOCK_DGRAM, 0);
	for (int i = 0; i < 20; i++)
	{
		bombs[i].coordinates = -1;
		bombs[i].countdown = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		packet.id[i] = -1;
	}
	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bomb_counter, NULL, 0, &threadId);
	int res = bind(sockServ, (struct sockaddr*)&addrServ, sizeof(addrServ));
	for (int i = 0; i < LINE_LENGTH * COLUMNS; i++)
	{
		packet.map[i] = map_1[i];
	}

	std::srand(GetTickCount());
	for (int i = 0; i < LINE_LENGTH; i++)
	{
		int j = 0;
		for (int k = 0; k < LINE_LENGTH; k++)
		{
			if (packet.map[k + i * LINE_LENGTH] == BLOCK_EMPTY && 
				packet.map[k + i * LINE_LENGTH + 1] != BLOCK_SPAWN &&
				packet.map[k + i * LINE_LENGTH - 1] != BLOCK_SPAWN &&
				packet.map[k + i * LINE_LENGTH + LINE_LENGTH] != BLOCK_SPAWN &&
				packet.map[k + i * LINE_LENGTH - LINE_LENGTH] != BLOCK_SPAWN)
			{
				int chance = std::rand() % 100;
				if (chance < 50)
				{
					packet.map[k + i * LINE_LENGTH] = BLOCK_CRATE;
				}
			}
		}
	}
	while (1)
	{
		int id = -1;
		int len = sizeof(addrClient);
		char bufServ[1024] = {};
		bytes_read = recvfrom(sockServ, bufServ, 1024, 0, (struct sockaddr*)&addrClient, &len);
		int* key = (int*)bufServ;
		if (*key == 123)
		{
			printf("Connected");
			for (int n = 0; n < MAX_PLAYERS; n++)
			{
				if (packet.id[n] == -1)
				{
					id = pow(2, (n+1));
					sendto(sockServ, (char*)&id, sizeof(int), 0, (struct sockaddr*)&addrClient, len);
					break;
				}
			}
			if (id == -1)
			{
				continue;
			}
			for (int i = 0; i < LINE_LENGTH; i++)
			{
				int j = 0;
				for (int k = 0; k < LINE_LENGTH; k++)
				{
					if (packet.map[k + i * 13] == BLOCK_SPAWN)
					{
						for (int n = 0; n < MAX_PLAYERS; n++)
						{
							if (packet.id[n] == -1)
							{
								packet.map[k + i * 13] = pow(2, (n + 1));
								packet.id[n] = pow(2, (n + 1));
								players[id] = { packet.id[n] };
								break;
							}
						}
						sendto(sockServ, (char*)&packet, sizeof(packet), 0, (struct sockaddr*)&addrClient, len);
						j = 1;
						break;
					}
				}
				if (j != 0)
				{
					break;
				}
			}
			player_amt++;
		}
		else
		{
			int p_coord = -1;
			message* msg_recv = (message*)bufServ;
			for (int j = 0; j < LINE_LENGTH * COLUMNS; j++)
			{
				if (packet.map[j] == msg_recv->second || packet.map[j] == msg_recv->second + BLOCK_BOMB_1 || packet.map[j] - BLOCK_UPGRADE1 == msg_recv->second)
				{
					p_coord = j;
					break;
				}
			}
			if (bytes_read != -1 && msg_recv->second != 0 && p_coord != -1)
			{
				if (msg_recv->first == PACKET_BOMB && players[msg_recv->second].bombs > 0)
				{
					if (packet.map[p_coord] == msg_recv->second || packet.map[p_coord] - BLOCK_UPGRADE1 == msg_recv->second)
					{
						for (int i = 0; i <= 20; i++)
						{
							if (i == 20)
							{
								break;
							}
							if (bombs[i].coordinates == BLOCK_NULL)
							{
								players[msg_recv->second].bombs -= 1;
								bombs[i].id = msg_recv->second;
								bombs[i].coordinates = p_coord;
								bombs[i].countdown = 200;
								packet.map[bombs[i].coordinates] += BLOCK_BOMB_1;
								break;
							}
						}
					}
				}
				else
				{
					switch (msg_recv->first)
					{
					case PACKET_UP:
						if (packet.map[p_coord - LINE_LENGTH] == BLOCK_EMPTY || (packet.map[p_coord - LINE_LENGTH] == BLOCK_UPGRADE1) || (packet.map[p_coord - LINE_LENGTH] == BLOCK_UPGRADE2))
						{
							if (packet.map[p_coord - LINE_LENGTH] == BLOCK_UPGRADE1)
							{
								players[msg_recv->second].upgrades["shield"] = TRUE;
							}
							if (packet.map[p_coord - LINE_LENGTH] == BLOCK_UPGRADE2)
							{
								players[msg_recv->second].bombs++;
								players[msg_recv->second].bombs_max++;
							}
							packet.map[p_coord] -= msg_recv->second;
							packet.map[p_coord - LINE_LENGTH] = msg_recv->second;
						}
						break;
					case PACKET_DOWN:
						if (packet.map[p_coord + LINE_LENGTH] == BLOCK_EMPTY || (packet.map[p_coord + LINE_LENGTH] == BLOCK_UPGRADE1) || (packet.map[p_coord + LINE_LENGTH] == BLOCK_UPGRADE2))
						{
							if (packet.map[p_coord + LINE_LENGTH] == BLOCK_UPGRADE1)
							{
								players[msg_recv->second].upgrades["shield"] = TRUE;
							}
							if (packet.map[p_coord + LINE_LENGTH] == BLOCK_UPGRADE2)
							{
								players[msg_recv->second].bombs++;
								players[msg_recv->second].bombs_max++;
							}
							packet.map[p_coord] -= msg_recv->second;
							packet.map[p_coord + LINE_LENGTH] = msg_recv->second;
						}
						break;
					case PACKET_LEFT:

						if (packet.map[p_coord - 1] == BLOCK_EMPTY || (packet.map[p_coord - 1] == BLOCK_UPGRADE1) || (packet.map[p_coord - 1] == BLOCK_UPGRADE2))
						{
							if (packet.map[p_coord - 1] == BLOCK_UPGRADE1)
							{
								players[msg_recv->second].upgrades["shield"] = TRUE;
							}
							if (packet.map[p_coord - 1] == BLOCK_UPGRADE2)
							{
								players[msg_recv->second].bombs++;
								players[msg_recv->second].bombs_max++;
							}
							packet.map[p_coord] -= msg_recv->second;
							packet.map[p_coord - 1] = msg_recv->second;
						}
						break;
					case PACKET_RIGHT:
						if (packet.map[p_coord + 1] == BLOCK_EMPTY || (packet.map[p_coord + 1] == BLOCK_UPGRADE1) || (packet.map[p_coord + 1] == BLOCK_UPGRADE2))
						{
							if (packet.map[p_coord + 1] == BLOCK_UPGRADE1)
							{
								players[msg_recv->second].upgrades["shield"] = TRUE;
							}
							if (packet.map[p_coord + 1] == BLOCK_UPGRADE2)
							{
								players[msg_recv->second].bombs ++;
								players[msg_recv->second].bombs_max ++;
							}
							packet.map[p_coord] -= msg_recv->second;
							packet.map[p_coord + 1] = msg_recv->second;
						}
						break;
					}
				}
				sendto(sockServ, (char*)&packet, sizeof(packet), 0, (struct sockaddr*)&addrClient, len);
			}

		}
	}
#ifdef _WIN32
	closesocket(sockServ);
#else
	close(sockServ);
#endif
	WSACleanup();
	return 0;
}