
#include <list>
#include <windows.h>
#include <hgesprite.h>
#include <hgefont.h>
#include "config.h"
#include "menuitem.h"
#include "GameFuncs.h"
#include "ConnectManager.h"
#include "Player.h"

bool frame_func()
{
	if (GameFuncs::GetInstance()->GetMenu() == "main_menu")
	{
		return GameFuncs::GetInstance()->MainMenu();
	} else 	if (GameFuncs::GetInstance()->GetMenu() == "connect")
	{
		GameFuncs::GetInstance()->Connect();
	} else 	if (GameFuncs::GetInstance()->GetMenu() == "game")
	{
		GameFuncs::GetInstance()->Game();
	} else 	if (GameFuncs::GetInstance()->GetMenu() == "disconnected")
	{
		GameFuncs::GetInstance()->Disconnect();
	}
	return false;
}

bool render_func()
{
	ResMng* rmng = ResMng::GetInstance();
	rmng->GetHge()->Gfx_BeginScene();
	rmng->GetHge()->Gfx_Clear(0);

	hgeGUI* gui = ResMng::GetInstance()->GetGui();
	hgeGUI* gui_connect = ResMng::GetInstance()->GetGuiConnect();
	if (GameFuncs::GetInstance()->GetMenu() == "main_menu")
	{
		gui->Render();
	}
	if (GameFuncs::GetInstance()->GetMenu() == "connect" || GameFuncs::GetInstance()->GetMenu() == "disconnected")
	{
		gui_connect->Render();
	}
	if (GameFuncs::GetInstance()->GetMenu() == "game")
	{
		rmng->GetSprite(RES_SPRITE_BACK)->Render(0, 0);
		EnterCriticalSection(GameFuncs::GetInstance()->GetCriticalSection());
		for (const auto& o : GameFuncs::GetInstance()->GetObjectList())
		{
			o->Draw();
		}
		LeaveCriticalSection(GameFuncs::GetInstance()->GetCriticalSection());
	}
	rmng->GetHge()->Gfx_EndScene();
	return false;
}

void GameFuncs::Game()
{
	if (ConnectManager::GetInstance()->ConnectionStatus() == DISCONNECTED)
	{
		m_menu = "disconnected";
	}
	static unsigned long g_last_time = GetTickCount();
	if (GetTickCount() - g_last_time < 200)
	{
		return;
	}
	g_last_time = GetTickCount();

	if (m_hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		m_key_lastid = 0;
		m_hge_gui->SetFocus(1);
		m_hge_gui->Enter();
		m_menu = "main_menu";
	}

	const vector<hgeKeyCode_t> keys = { HGEK_LEFT, HGEK_RIGHT, HGEK_UP, HGEK_DOWN, HGEK_SPACE };
	for (const auto& k : keys)
	{
		if (m_hge->Input_GetKeyState(k))
		{
			Player::GetInstance()->KeyProcessing(k);
			break;
		}
	}
}

void GameFuncs::Connect()
{
	auto& gui_text = *(hgeGUIText*)m_hge_gui_connect->GetCtrl(3);
	gui_text.SetText(m_ip.c_str());
	switch (m_hge->Input_GetChar())
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
		m_ip.push_back(m_hge->Input_GetChar());
		break;
	}
	case HGEK_ESCAPE:
	{
		m_key_lastid = 0;
		m_hge_gui->SetFocus(1);
		m_hge_gui->Enter();
		m_menu = "main_menu";
		break;
	}
	case HGEK_ENTER:
	{
		ConnectManager::GetInstance()->SetSockAddrAndPort(m_ip);
		ConnectManager::GetInstance()->ConnectThread();
		m_menu = "game";
		break;
	}
	case HGEK_BACKSPACE:
		m_ip.pop_back();
		break;
	}
}

void GameFuncs::Disconnect()
{
	if (flag == true)
	{
		delay = GetTickCount();
		flag = false;
	}
	std::string message = "You were disconnected";
	auto& gui_text = *(hgeGUIText*)m_hge_gui_connect->GetCtrl(3);
	gui_text.SetText(message.c_str());
	if (GetTickCount() - delay > 1000)
	{
		m_key_lastid = 0;
		m_key_id = -1;
		m_hge_gui->SetFocus(1);
		m_hge_gui->Enter();
		m_menu = "main_menu";
		flag = true;
	}
}

bool GameFuncs::MainMenu()
{
	const auto dt = m_hge->Timer_GetDelta();
	m_key_id = m_hge_gui->Update(dt);
	if (m_key_id == -1)
	{
		switch (m_key_lastid)
		{
		case 1:
			m_menu = "game";
			break;
		case 2:
			m_menu = "connect";
			break;
		case 5:
			return true;
		}
	}
	else if (m_key_id)
	{
		m_key_lastid = m_key_id;
		m_hge_gui->Leave();
	}
	return false;
}

GameFuncs* GameFuncs::GetInstance()
{
	static GameFuncs* instance = nullptr;
	if (!instance)
	{
		instance = new GameFuncs();
	}
	return instance;
}

void GameFuncs::ReleaseObjectList()
{
	for (auto& o : m_ObjectList)
	{
		if (o != Player::GetInstance())
		{
			delete(o);
		}
	}
	m_ObjectList.clear();
}