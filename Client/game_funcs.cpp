
#include "game_functions.h"
#include "ConnectManager.h"
#include <hge.h>
#include <list>
#include <string>
#include "Object.h"
#include "ResMng.h"
#include "menuitem.h"
#include <windows.h>
#include "config.h"
#include <hgesprite.h>
#include <cassert>
#include <hgefont.h>
#include <hgegui.h>
#include "Player.h"



#define CMNG ConnectManager::GetInstance()


std::string menu = "main_menu";
std::list<Object*> gObjectList = {};
extern CRITICAL_SECTION CriticalSection;

bool frame_func()
{

	hgeGUI* gui = ResMng::GetInstance()->GetGui();
	hgeGUI* gui_connect = ResMng::GetInstance()->GetGuiConnect();
	HGE* hge = ResMng::GetInstance()->GetHge();
	static int lastid = 0;
	static int id = -1;
	if (menu == "main_menu")
	{
		const auto dt = hge->Timer_GetDelta();
		id = gui->Update(dt);
		if (id == -1)
		{
			switch (lastid)
			{
			case 1:
				menu = "game";
				break;
			case 2:
				menu = "connect";
				break;
			case 5:
				return true;
			}
		}
		else if (id)
		{
			lastid = id;
			gui->Leave();
		}
	}
	if (menu == "connect")
	{
		static std::string ip = "192.168.1.48";
		auto& gui_text = *(hgeGUIText*)gui_connect->GetCtrl(3);
		gui_text.SetText(ip.c_str());
		switch (hge->Input_GetChar())
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
		{
			ip.push_back(hge->Input_GetChar());
			break;
		}
		case HGEK_BACKSPACE:
			ip.pop_back();
			break;
		}

		if (hge->Input_GetKey() == HGEK_ENTER)
		{
			ConnectManager::GetInstance()->SetSockAddrAndPort(ip);
			ConnectManager::GetInstance()->ConnectInit();
			menu = "game";
			return false;
		}
		if (hge->Input_GetKey() == HGEK_ESCAPE)
		{
			lastid = 0;
			gui->SetFocus(1);
			gui->Enter();
			menu = "main_menu";
		}
	}
	if (menu == "game")
	{
		if (ConnectManager::GetInstance()->ConnectionStatus() == DISCONNECTED)
		{
			menu = "disconnected";
		}
		static unsigned long g_last_time = GetTickCount();
		if (GetTickCount() - g_last_time < 200)
		{
			return false;
		}
		g_last_time = GetTickCount();

		if (hge->Input_GetKeyState(HGEK_ESCAPE))
		{
			lastid = 0;
			gui->SetFocus(1);
			gui->Enter();
			menu = "main_menu";
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
	if (menu == "disconnected")
	{
		static int delay = GetTickCount();
		static string message = "You were disconnected";
		auto& gui_text = *(hgeGUIText*)gui_connect->GetCtrl(3);
		gui_text.SetText(message.c_str());
		if (GetTickCount() - delay > 1000)
		{
			lastid = 0;
			id = -1;
			gui->SetFocus(1);
			gui->Enter();
			menu = "main_menu";
		}
		return false;
	}
}


bool render_func()
{
	ResMng* rmng = ResMng::GetInstance();
	rmng->GetHge()->Gfx_BeginScene();
	rmng->GetHge()->Gfx_Clear(0);

	hgeGUI* gui = ResMng::GetInstance()->GetGui();
	hgeGUI* gui_connect = ResMng::GetInstance()->GetGuiConnect();
	if (menu == "main_menu")
	{
		gui->Render();
	}
	if (menu == "connect" || menu == "disconnected")
	{
		gui_connect->Render();
	}
	if (menu == "game")
	{
		rmng->GetSprite(RES_SPRITE_BACK)->Render(0, 0);
		EnterCriticalSection(&CriticalSection);
		for (const auto& o : gObjectList)
		{
			o->Draw();
		}
		LeaveCriticalSection(&CriticalSection);
	}
	rmng->GetHge()->Gfx_EndScene();
	return false;
}