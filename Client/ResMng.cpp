
#include <hge.h>
#include "ResMng.h"
#include"game_functions.h"
#include "config.h"
#include "Player.h"


static int hgeInit(HGE** h)
{
	(*h) = hgeCreate(HGE_VERSION);
	(*h)->System_SetState(HGE_LOGFILE, "bomber.log");
	(*h)->System_SetState(HGE_FRAMEFUNC, frame_func);
	(*h)->System_SetState(HGE_RENDERFUNC, render_func);
	(*h)->System_SetState(HGE_TITLE, "Game Demo");
	(*h)->System_SetState(HGE_FPS, 100);
	(*h)->System_SetState(HGE_WINDOWED, true);
	(*h)->System_SetState(HGE_SCREENWIDTH, SCREENWIDTH);
	(*h)->System_SetState(HGE_SCREENHEIGHT, SCREENHEIGHT);
	(*h)->System_SetState(HGE_SCREENBPP, 16);
	(*h)->System_SetState(HGE_DONTSUSPEND, true);
	return (*h)->System_Initiate();
}

//static


ResMng* ResMng::GetInstance()
{
	static ResMng* instance;
	if (!instance)
	{
		instance = new ResMng();
	}
	return instance;
}

hgeSprite* ResMng::GetSprite(int ent_id)
{
	for (auto& e : entities)
	{
		if (e.second.id == ent_id)
		{
			return e.second.sprite;
		}
	}
}

HEFFECT ResMng::GetSound(int ent_id)
{
	for (auto& e : entities)
	{
		if (e.second.id == ent_id)
		{
			return e.second.sound;
		}
	}
}

hgeSprite* ResMng::CreateSprite(HTEXTURE tex, int color)
{
	auto sprite = new hgeSprite(tex, 0, 0, TEX_SIZE, TEX_SIZE);
	if (tex == back)
	{
		sprite = new hgeSprite(tex, 0, 0, BACK_SIZE, BACK_SIZE);
	}
	if (color != NULL)
	{
		sprite->SetColor(color);
	}
	if (tex == back)
	{
		sprite->SetHotSpot(0, 0);
	}
	else
	{
		sprite->SetHotSpot(16, 16);
	}
	return sprite;
}

HTEXTURE ResMng::GetPlayerTex(string key, int id)
{
	return player[id][key];
}

ResMng::ResMng()
{
	hgeInit(&m_hge);
	block = m_hge->Texture_Load("../pic/block.png");
	brick = m_hge->Texture_Load("../pic/brick.png");
	bomb_1 = m_hge->Texture_Load("../pic/bomb.png");
	bomb_2 = m_hge->Texture_Load("../pic/bomb_2.png");
	bomb_3 = m_hge->Texture_Load("../pic/bomb_3.png");
	back = m_hge->Texture_Load("../pic/back.png");
	shield_upg = m_hge->Texture_Load("../pic/shield.png");
	player[PLAYER1]["still_forward"] = m_hge->Texture_Load("../pic/red/player_still_forward.png");
	player[PLAYER1]["walk1_forward"] = m_hge->Texture_Load("../pic/red/player_walk1_forward.png");
	player[PLAYER1]["walk1_left"] = m_hge->Texture_Load("../pic/red/player_walk1_left.png");
	player[PLAYER1]["walk1_right"] = m_hge->Texture_Load("../pic/red/player_walk1_right.png");
	player[PLAYER1]["walk1_backward"] = m_hge->Texture_Load("../pic/red/player_walk1_backward.png");
	player[PLAYER1]["walk2_forward"] = m_hge->Texture_Load("../pic/red/player_walk2_forward.png");
	player[PLAYER1]["walk2_backward"] = m_hge->Texture_Load("../pic/red/player_walk2_backward.png");
	player[PLAYER1]["walk2_right"] = m_hge->Texture_Load("../pic/red/player_walk2_right.png");
	player[PLAYER1]["walk2_left"] = m_hge->Texture_Load("../pic/red/player_walk2_left.png");
	player[PLAYER1]["still_left"] = m_hge->Texture_Load("../pic/red/player_still_left.png");
	player[PLAYER1]["still_right"] = m_hge->Texture_Load("../pic/red/player_still_right.png");
	player[PLAYER1]["still_backward"] = m_hge->Texture_Load("../pic/blue/player_still_backward.png");
	player[PLAYER2]["still_forward"] = m_hge->Texture_Load("../pic/blue/player_still_forward.png");
	player[PLAYER2]["walk1_forward"] = m_hge->Texture_Load("../pic/blue/player_walk1_forward.png");
	player[PLAYER2]["walk1_left"] = m_hge->Texture_Load("../pic/blue/player_walk1_left.png");
	player[PLAYER2]["walk1_right"] = m_hge->Texture_Load("../pic/blue/player_walk1_right.png");
	player[PLAYER2]["walk1_backward"] = m_hge->Texture_Load("../pic/blue/player_walk1_backward.png");
	player[PLAYER2]["walk2_forward"] = m_hge->Texture_Load("../pic/blue/player_walk2_forward.png");
	player[PLAYER2]["walk2_backward"] = m_hge->Texture_Load("../pic/blue/player_walk2_backward.png");
	player[PLAYER2]["walk2_right"] = m_hge->Texture_Load("../pic/blue/player_walk2_right.png");
	player[PLAYER2]["walk2_left"] = m_hge->Texture_Load("../pic/blue/player_walk2_left.png");
	player[PLAYER2]["still_left"] = m_hge->Texture_Load("../pic/blue/player_still_left.png");
	player[PLAYER2]["still_right"] = m_hge->Texture_Load("../pic/blue/player_still_right.png");
	player[PLAYER2]["still_backward"] = m_hge->Texture_Load("../pic/blue/player_still_backward.png");
	player[PLAYER3]["still_forward"] = m_hge->Texture_Load("../pic/green/player_still_forward.png");
	player[PLAYER3]["walk1_forward"] = m_hge->Texture_Load("../pic/green/player_walk1_forward.png");
	player[PLAYER3]["walk1_left"] = m_hge->Texture_Load("../pic/green/player_walk1_left.png");
	player[PLAYER3]["walk1_right"] = m_hge->Texture_Load("../pic/green/player_walk1_right.png");
	player[PLAYER3]["walk1_backward"] = m_hge->Texture_Load("../pic/green/player_walk1_backward.png");
	player[PLAYER3]["walk2_forward"] = m_hge->Texture_Load("../pic/green/player_walk2_forward.png");
	player[PLAYER3]["walk2_backward"] = m_hge->Texture_Load("../pic/green/player_walk2_backward.png");
	player[PLAYER3]["walk2_right"] = m_hge->Texture_Load("../pic/green/player_walk2_right.png");
	player[PLAYER3]["walk2_left"] = m_hge->Texture_Load("../pic/green/player_walk2_left.png");
	player[PLAYER3]["still_left"] = m_hge->Texture_Load("../pic/green/player_still_left.png");
	player[PLAYER3]["still_right"] = m_hge->Texture_Load("../pic/green/player_still_right.png");
	player[PLAYER3]["still_backward"] = m_hge->Texture_Load("../pic/green/player_still_backward.png");
	player[PLAYER4]["still_forward"] = m_hge->Texture_Load("../pic/yellow/player_still_forward.png");
	player[PLAYER4]["walk1_forward"] = m_hge->Texture_Load("../pic/yellow/player_walk1_forward.png");
	player[PLAYER4]["walk1_left"] = m_hge->Texture_Load("../pic/yellow/player_walk1_left.png");
	player[PLAYER4]["walk1_right"] = m_hge->Texture_Load("../pic/yellow/player_walk1_right.png");
	player[PLAYER4]["walk1_backward"] = m_hge->Texture_Load("../pic/yellow/player_walk1_backward.png");
	player[PLAYER4]["walk2_forward"] = m_hge->Texture_Load("../pic/yellow/player_walk2_forward.png");
	player[PLAYER4]["walk2_backward"] = m_hge->Texture_Load("../pic/yellow/player_walk2_backward.png");
	player[PLAYER4]["walk2_right"] = m_hge->Texture_Load("../pic/yellow/player_walk2_right.png");
	player[PLAYER4]["walk2_left"] = m_hge->Texture_Load("../pic/yellow/player_walk2_left.png");
	player[PLAYER4]["still_left"] = m_hge->Texture_Load("../pic/yellow/player_still_left.png");
	player[PLAYER4]["still_right"] = m_hge->Texture_Load("../pic/yellow/player_still_right.png");
	player[PLAYER4]["still_backward"] = m_hge->Texture_Load("../pic/yellow/player_still_backward.png");
	burn_1 = m_hge->Texture_Load("../pic/burn_1.png");
	burn_2 = m_hge->Texture_Load("../pic/burn_2.png");


	SetEnt(block, RES_SPRITE_WALL);
	SetEnt(shield_upg, RES_SPRITE_SHIELD);
	SetEnt(back, RES_SPRITE_BACK);
	SetEnt(brick, RES_SPRITE_CRATE);
	SetEnt(bomb_1, RES_SPRITE_BOMB_1);
	SetEnt(bomb_2, RES_SPRITE_BOMB_2);
	SetEnt(bomb_3, RES_SPRITE_BOMB_3);
	SetEnt(player[PLAYER1]["still_forward"], RES_SPRITE_PLAYER_00);
	SetEnt(player[PLAYER2]["still_forward"], RES_SPRITE_PLAYER_01);
	SetEnt(player[PLAYER3]["still_forward"], RES_SPRITE_PLAYER_02);
	SetEnt(player[PLAYER4]["still_forward"], RES_SPRITE_PLAYER_03);
	SetEnt(burn_1, RES_SPRITE_BURN_1, ORANGE);
	SetEnt(burn_2, RES_SPRITE_BURN_2, ORANGE);
}

ResMng::~ResMng()
{
	m_hge->Texture_Free(block);
	m_hge->Texture_Free(burn_1);
	m_hge->Texture_Free(burn_2);
	m_hge->System_Shutdown();
	m_hge->Release();
}
