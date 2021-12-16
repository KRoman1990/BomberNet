
#include <hge.h>
#include <hgesprite.h>
#include <cassert>
#include"game_functions.h"
#include "config.h"
#include "ConnectManager.h"
#include <list>
#include "Object.h"
#include "Player.h"
#include "ResMng.h"

#define CMNG ConnectManager::GetInstance()

std::list<Object*> gObjectList = {};

extern CRITICAL_SECTION CriticalSection;

bool frame_func()
{
	static unsigned long g_last_time = GetTickCount();
	if (GetTickCount() - g_last_time < 200)
	{
		return false;
	}
	g_last_time = GetTickCount();

	HGE* hge = ResMng::GetInstance()->GetHge();
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) {
		return true;
	}

	const vector<hgeKeyCode_t> keys = { HGEK_LEFT, HGEK_RIGHT, HGEK_UP, HGEK_DOWN, HGEK_SPACE };
	for (const auto& k : keys)
	{
		if (hge->Input_GetKeyState(k))
		{
			Player::GetInstance()->KeyProcessing(k);
			break;
		}
	}
	return false;
}


bool render_func() {
	ResMng* rmng = ResMng::GetInstance();

	rmng->GetHge()->Gfx_BeginScene();
	rmng->GetHge()->Gfx_Clear(0);

	rmng->GetSprite(RES_SPRITE_BACK)->Render(0, 0);
	EnterCriticalSection(&CriticalSection);
	for (const auto& o : gObjectList)
	{
		o->Draw();
	}
	LeaveCriticalSection(&CriticalSection);
	rmng->GetHge()->Gfx_EndScene();

	return false;
}
