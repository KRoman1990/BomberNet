#pragma once
#define LINE_LENGTH 13
#define COLUMNS 13
#define MAX_PLAYERS 4
#define TEX_SIZE 32
#define BACK_SIZE 624
#define PLAYER_CODE 99
#define SCREENWIDTH 624
#define SCREENHEIGHT 624
#define SCREEN_MERGE 24
#define MAGIC_CONNECT_KEY 123
#define CONNECT_PORT 7689

enum entities
{
	BLOCK_PLAYER1 = 2,
	BLOCK_PLAYER2 = 4,
	BLOCK_PLAYER3 = 8,
	BLOCK_PLAYER4 = 16,
	BLOCK_NULL = -1,
	BLOCK_SPAWN = 2048,
	BLOCK_EMPTY = 0,
	BLOCK_WALL = 1,
	BLOCK_CRATE = 32,
	BLOCK_BOMB_1 = 64,
	BLOCK_BOMB_2 = 128,
	BLOCK_BOMB_3 = 256,
	BLOCK_BURNING_1 = 512,
	BLOCK_UPGRADE_SHIELD = 1024,
	BLOCK_UPGRADE_MANYBOMBS = 4096,
	BLOCK_UPGRADE_BOMBRANGE = 8192
};

enum colors
{
	GREEN = 0xFF50FF50,
	BLUE = 0xFF5050FF,
	YELLOW = 0xFFFFFF50,
	RED = 0xFFFF5050,
	ORANGE = 0xFFFFA000,
	GREY = 0xFFF0F0F0,
	LIGHT_GREY = 0xFFA0A0A0,
	BRICK = 0xFFFF9090
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

enum anim
{
	STILL = 0,
	WALK1 = 1,
	WALK2 = 2
};

enum Commands
{
	PACKET_UP = 0,
	PACKET_RIGHT = 1,
	PACKET_DOWN = 2,
	PACKET_LEFT = 3,
	PACKET_BOMB = 4,
	PACKET_HEARTBEAT = 5
};

enum ServState
{
	CONNECTED = 0,
	DISCONNECTED = 1
};