
#include <hge.h>
#include "ResMng.h"
#include "menuitem.h"
#include "GameFuncs.h"
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
	assert(0);
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
	assert(0);
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
	crs_tex = m_hge->Texture_Load("../pic/cursor.png");
	bomb_1 = m_hge->Texture_Load("../pic/bomb.png");
	bomb_2 = m_hge->Texture_Load("../pic/bomb_2.png");
	bomb_3 = m_hge->Texture_Load("../pic/bomb_3.png");
	back = m_hge->Texture_Load("../pic/back.png");
	shield_upg = m_hge->Texture_Load("../pic/shield.png");
	shield_spr = m_hge->Texture_Load("../pic/shield_on_player.png");
	bombs_upg = m_hge->Texture_Load("../pic/bombs.png");
	range_upg = m_hge->Texture_Load("../pic/range.png");
	player[BLOCK_PLAYER1]["still_forward"] = m_hge->Texture_Load("../pic/red/player_still_forward.png");
	player[BLOCK_PLAYER1]["walk1_forward"] = m_hge->Texture_Load("../pic/red/player_walk1_forward.png");
	player[BLOCK_PLAYER1]["walk1_left"] = m_hge->Texture_Load("../pic/red/player_walk1_left.png");
	player[BLOCK_PLAYER1]["walk1_right"] = m_hge->Texture_Load("../pic/red/player_walk1_right.png");
	player[BLOCK_PLAYER1]["walk1_backward"] = m_hge->Texture_Load("../pic/red/player_walk1_backward.png");
	player[BLOCK_PLAYER1]["walk2_forward"] = m_hge->Texture_Load("../pic/red/player_walk2_forward.png");
	player[BLOCK_PLAYER1]["walk2_backward"] = m_hge->Texture_Load("../pic/red/player_walk2_backward.png");
	player[BLOCK_PLAYER1]["walk2_right"] = m_hge->Texture_Load("../pic/red/player_walk2_right.png");
	player[BLOCK_PLAYER1]["walk2_left"] = m_hge->Texture_Load("../pic/red/player_walk2_left.png");
	player[BLOCK_PLAYER1]["still_left"] = m_hge->Texture_Load("../pic/red/player_still_left.png");
	player[BLOCK_PLAYER1]["still_right"] = m_hge->Texture_Load("../pic/red/player_still_right.png");
	player[BLOCK_PLAYER1]["still_backward"] = m_hge->Texture_Load("../pic/blue/player_still_backward.png");
	player[BLOCK_PLAYER2]["still_forward"] = m_hge->Texture_Load("../pic/blue/player_still_forward.png");
	player[BLOCK_PLAYER2]["walk1_forward"] = m_hge->Texture_Load("../pic/blue/player_walk1_forward.png");
	player[BLOCK_PLAYER2]["walk1_left"] = m_hge->Texture_Load("../pic/blue/player_walk1_left.png");
	player[BLOCK_PLAYER2]["walk1_right"] = m_hge->Texture_Load("../pic/blue/player_walk1_right.png");
	player[BLOCK_PLAYER2]["walk1_backward"] = m_hge->Texture_Load("../pic/blue/player_walk1_backward.png");
	player[BLOCK_PLAYER2]["walk2_forward"] = m_hge->Texture_Load("../pic/blue/player_walk2_forward.png");
	player[BLOCK_PLAYER2]["walk2_backward"] = m_hge->Texture_Load("../pic/blue/player_walk2_backward.png");
	player[BLOCK_PLAYER2]["walk2_right"] = m_hge->Texture_Load("../pic/blue/player_walk2_right.png");
	player[BLOCK_PLAYER2]["walk2_left"] = m_hge->Texture_Load("../pic/blue/player_walk2_left.png");
	player[BLOCK_PLAYER2]["still_left"] = m_hge->Texture_Load("../pic/blue/player_still_left.png");
	player[BLOCK_PLAYER2]["still_right"] = m_hge->Texture_Load("../pic/blue/player_still_right.png");
	player[BLOCK_PLAYER2]["still_backward"] = m_hge->Texture_Load("../pic/blue/player_still_backward.png");
	player[BLOCK_PLAYER3]["still_forward"] = m_hge->Texture_Load("../pic/green/player_still_forward.png");
	player[BLOCK_PLAYER3]["walk1_forward"] = m_hge->Texture_Load("../pic/green/player_walk1_forward.png");
	player[BLOCK_PLAYER3]["walk1_left"] = m_hge->Texture_Load("../pic/green/player_walk1_left.png");
	player[BLOCK_PLAYER3]["walk1_right"] = m_hge->Texture_Load("../pic/green/player_walk1_right.png");
	player[BLOCK_PLAYER3]["walk1_backward"] = m_hge->Texture_Load("../pic/green/player_walk1_backward.png");
	player[BLOCK_PLAYER3]["walk2_forward"] = m_hge->Texture_Load("../pic/green/player_walk2_forward.png");
	player[BLOCK_PLAYER3]["walk2_backward"] = m_hge->Texture_Load("../pic/green/player_walk2_backward.png");
	player[BLOCK_PLAYER3]["walk2_right"] = m_hge->Texture_Load("../pic/green/player_walk2_right.png");
	player[BLOCK_PLAYER3]["walk2_left"] = m_hge->Texture_Load("../pic/green/player_walk2_left.png");
	player[BLOCK_PLAYER3]["still_left"] = m_hge->Texture_Load("../pic/green/player_still_left.png");
	player[BLOCK_PLAYER3]["still_right"] = m_hge->Texture_Load("../pic/green/player_still_right.png");
	player[BLOCK_PLAYER3]["still_backward"] = m_hge->Texture_Load("../pic/green/player_still_backward.png");
	player[BLOCK_PLAYER4]["still_forward"] = m_hge->Texture_Load("../pic/yellow/player_still_forward.png");
	player[BLOCK_PLAYER4]["walk1_forward"] = m_hge->Texture_Load("../pic/yellow/player_walk1_forward.png");
	player[BLOCK_PLAYER4]["walk1_left"] = m_hge->Texture_Load("../pic/yellow/player_walk1_left.png");
	player[BLOCK_PLAYER4]["walk1_right"] = m_hge->Texture_Load("../pic/yellow/player_walk1_right.png");
	player[BLOCK_PLAYER4]["walk1_backward"] = m_hge->Texture_Load("../pic/yellow/player_walk1_backward.png");
	player[BLOCK_PLAYER4]["walk2_forward"] = m_hge->Texture_Load("../pic/yellow/player_walk2_forward.png");
	player[BLOCK_PLAYER4]["walk2_backward"] = m_hge->Texture_Load("../pic/yellow/player_walk2_backward.png");
	player[BLOCK_PLAYER4]["walk2_right"] = m_hge->Texture_Load("../pic/yellow/player_walk2_right.png");
	player[BLOCK_PLAYER4]["walk2_left"] = m_hge->Texture_Load("../pic/yellow/player_walk2_left.png");
	player[BLOCK_PLAYER4]["still_left"] = m_hge->Texture_Load("../pic/yellow/player_still_left.png");
	player[BLOCK_PLAYER4]["still_right"] = m_hge->Texture_Load("../pic/yellow/player_still_right.png");
	player[BLOCK_PLAYER4]["still_backward"] = m_hge->Texture_Load("../pic/yellow/player_still_backward.png");
	burn_1 = m_hge->Texture_Load("../pic/burn_1.png");
	burn_2 = m_hge->Texture_Load("../pic/burn_2.png");
	m_snd_menu = m_hge->Effect_Load("../sounds/menu.wav");
	m_font = new hgeFont("../pic/font1.fnt");
	m_font->SetColor(0xFFFFFFFF);

	SetEnt(block, RES_SPRITE_WALL);
	SetEnt(shield_upg, RES_SPRITE_SHIELD);
	SetEnt(shield_spr, RES_SPRITE_SHIELD_ON_PLAYER);
	SetEnt(bombs_upg, RES_SPRITE_MANYBOMBS);
	SetEnt(range_upg, RES_SPRITE_BOMBRANGE);
	SetEnt(back, RES_SPRITE_BACK);
	SetEnt(brick, RES_SPRITE_CRATE);
	SetEnt(bomb_1, RES_SPRITE_BOMB_1);
	SetEnt(bomb_2, RES_SPRITE_BOMB_2);
	SetEnt(bomb_3, RES_SPRITE_BOMB_3);
	SetEnt(player[BLOCK_PLAYER1]["still_forward"], RES_SPRITE_PLAYER_00);
	SetEnt(player[BLOCK_PLAYER2]["still_forward"], RES_SPRITE_PLAYER_01);
	SetEnt(player[BLOCK_PLAYER3]["still_forward"], RES_SPRITE_PLAYER_02);
	SetEnt(player[BLOCK_PLAYER4]["still_forward"], RES_SPRITE_PLAYER_03);
	SetEnt(burn_1, RES_SPRITE_BURN_1, ORANGE);
	SetEnt(crs_tex, RES_SPRITE_CURSOR);

	m_gui = new hgeGUI();
	m_gui_connect = new hgeGUI();

	m_gui->AddCtrl(new hgeGUIMenuItem(1, m_font, m_snd_menu, SCREENWIDTH / 2, SCREENHEIGHT / 3, 0.0f, "Play"));
	m_gui->AddCtrl(new hgeGUIMenuItem(2, m_font, m_snd_menu, SCREENWIDTH/2, SCREENHEIGHT/3 + 30, 0.0f, "Connect"));
	m_gui->AddCtrl(new hgeGUIMenuItem(5, m_font, m_snd_menu, SCREENWIDTH/2, SCREENHEIGHT/3 + 60, 0.4f, "Exit"));
	auto text = new hgeGUIText(3, SCREENWIDTH / 2 - 80, SCREENHEIGHT / 2 - 30, 0, 0, m_font);
	text->bVisible = true;
	text->SetText("Roman chudak");
	m_gui_connect->AddCtrl(text);

	m_gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	m_gui->SetCursor(entities[RES_SPRITE_CURSOR].sprite);
	m_gui->SetFocus(1);
	m_gui->Enter();
}

ResMng::~ResMng()
{
	m_hge->Texture_Free(block);
	m_hge->Texture_Free(burn_1);
	m_hge->Texture_Free(burn_2);
	m_hge->System_Shutdown();
	m_hge->Release();
}
