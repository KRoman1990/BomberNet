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
	BLOCK_BOMB = 6,
	BLOCK_BURNING_1 = 12,
	BLOCK_BURNING_2 = 13
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