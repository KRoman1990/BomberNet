#pragma once

#include <hge.h>
#include <list>
#include <windows.h>

#include "config.h"
#include "ConnectManager.h"
#include "Object.h"
#include "ResMng.h"

class Player : public Object
{
public:
	int GetId();
	int GetCoordPrev();
	void SetId(int id_recv);
	void SetCoordPrev(int prev_recv);
	void SetCoord(unsigned int coord) override;
	void SetUpgrade(int upg) { m_upg = upg; }
	unsigned int GetCoord() override;
	static Player* GetInstance();
	void KeyProcessing(hgeKeyCode_t key);
	void SendPack(Commands command);
	int GetAnim() { return animation_state; }
	void SetDirection(int dir);
	void SetAnim(int anim) { animation_state = anim; }
	HANDLE GetMutex() { return mut_coord; }
	hgeSprite* GetPlayerSprite();

	void Draw() override;

private:
	Player(unsigned int coord);
	Player()
	{
		mut_coord = CreateMutex(NULL, FALSE, "Coordintes");
		mut_id = CreateMutex(NULL, FALSE, "Id");
	}

	EntDesc player_sprite;
	int animation_state = 0;
	int m_player_coordinates_prev = -1;
	int m_id = 0;
	int m_upg = 0;
	HANDLE mut_coord;
	HANDLE mut_id;
};
