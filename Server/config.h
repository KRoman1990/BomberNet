#pragma once
#define LINE_LENGTH 13
#define COLUMNS 13
#define MAX_PLAYERS 4
#define TEX_SIZE 32
#define PLAYER_CODE 99

#define PLAYER1 100
#define PLAYER2 101
#define PLAYER3 102
#define PLAYER4 103

enum entities
{
	BLOCK_NULL = -1,
	BLOCK_EMPTY = 0,
	BLOCK_WALL = 9,
	BLOCK_CRATE = 5,
	BLOCK_BOMB_1 = 6,
	BLOCK_BOMB_2 = 7,
	BLOCK_BOMB_3 = 8,
	BLOCK_BURNING_1 = 12,
	BLOCK_UPGRADE1 = 13
};

enum colors
{
	GREEN = 0xFF50FF50,
	BLUE = 0xFF5050FF,
	YELLOW = 0xFFFFFF50,
	RED = 0xFFFF5050,
	WHITE = 0xFFFFFFFF,
	GREY = 0xA0FFFFFF,
	DARK_BROWN = 0xA0FFAB00,
	LIGHT_BROWN = 0xFFFFAB00,
	BRICK = 0xFFFFA0A0
};

enum player_code
{
	PLAYER_1 = 100,
	PLAYER_2 = 101,
	PLAYER_3 = 102,
	PLAYER_4 = 103
};

enum directions
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

enum packets
{
	PACKET_UP = 0,
	PACKET_RIGHT = 1,
	PACKET_DOWN = 2,
	PACKET_LEFT = 3,
	PACKET_BOMB = 4,
	PACKET_HEARTBEAT = 5
};