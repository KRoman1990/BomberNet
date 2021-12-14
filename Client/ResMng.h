#pragma once
#include <vector>
#include <map>
#include <string>
#include <hge.h>
#include <hgesprite.h>
#include <windows.h>
#include "config.h"

struct EntDesc
{
	hgeSprite* sprite;
	HEFFECT sound;
	int id;
};

using namespace std;

#define RES_SPRITE_PLAYER_00 100
#define RES_SPRITE_PLAYER_01 101
#define RES_SPRITE_PLAYER_02 102
#define RES_SPRITE_PLAYER_03 103
#define RES_SPRITE_WALL      110
#define RES_SPRITE_CRATE     111
#define RES_SPRITE_BOMB_1      1120
#define RES_SPRITE_BOMB_2      1121
#define RES_SPRITE_BOMB_3      1122
#define RES_SPRITE_BACK      113
#define RES_SPRITE_BURN_1    120
#define RES_SPRITE_BURN_2    121
#define RES_SPRITE_SHIELD    130

class ResMng
{
public:

	~ResMng();

	hgeSprite* GetSprite(int ent_id);
	HEFFECT GetSound(int ent_id);
	static ResMng* GetInstance();
	HGE* GetHge() { return m_hge; }
	EntDesc SetEnt(HTEXTURE ent_tex, int ent_id, int color = NULL, HEFFECT ent_snd = NULL) { entities[ent_id] = { CreateSprite(ent_tex, color), ent_snd, ent_id }; return entities[ent_id]; }
	HTEXTURE GetPlayerTex(string key, int id);

private:

	ResMng();
	hgeSprite* CreateSprite(HTEXTURE tex, int color);
	HGE* m_hge = nullptr;
	map<int, EntDesc> entities;
	HTEXTURE burn_1;
	HTEXTURE burn_2;
	HTEXTURE block;
	HTEXTURE brick;
	HTEXTURE bomb_1;
	HTEXTURE bomb_2;
	HTEXTURE bomb_3;
	HTEXTURE shield_upg;
	HTEXTURE back;
	map<int, map<string, HTEXTURE>> player;
};
