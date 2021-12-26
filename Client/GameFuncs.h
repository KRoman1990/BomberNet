#pragma once

#include <hge.h>
#include <hgegui.h>
#include <string>
#include <cassert>
#include "ResMng.h"
#include "Object.h"

bool frame_func();
bool render_func();

class GameFuncs
{
public:
	static GameFuncs* GetInstance();
	void Game();
	bool MainMenu();
	void Disconnect();
	void Connect();
	void SetMenu(std::string g_menu) { m_menu = g_menu; }
	const std::string GetMenu() const { return m_menu; }
	const std::list<Object*>& GetObjectList() const { return m_ObjectList; }
	void AddObjectList(Object* object) { m_ObjectList.push_back(object); }
	void ReleaseObjectList();
	CRITICAL_SECTION* GetCriticalSection() { return &m_ObjectCriticalSection; }
	~GameFuncs()
	{
		DeleteCriticalSection(&m_ObjectCriticalSection);
		ReleaseObjectList();
	}
private:
	GameFuncs()
	{
		m_hge = ResMng::GetInstance()->GetHge();
		m_hge_gui_connect = ResMng::GetInstance()->GetGuiConnect();
		m_hge_gui = ResMng::GetInstance()->GetGui();
		assert(InitializeCriticalSectionAndSpinCount(&m_ObjectCriticalSection, 0x00000400));
		m_menu = "main_menu";
		m_ip = "192.168.1.48";
		delay = GetTickCount();
		flag = true;
	}
	unsigned long delay;
	CRITICAL_SECTION m_ObjectCriticalSection;
	std::list<Object*> m_ObjectList = {};
	hgeGUI* m_hge_gui;
	hgeGUI* m_hge_gui_connect;
	HGE* m_hge;
	std::string m_menu;
	std::string m_ip;
	bool flag;
	int m_key_lastid = 0;
	int m_key_id = -1;
};