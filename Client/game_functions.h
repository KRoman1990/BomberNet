#pragma once
#include <hge.h>
#include <hgesprite.h>
#include <cassert>
#include <hgefont.h>
#include <hgegui.h>
#include <list>
#include <string>
#include <windows.h>
#include "config.h"
#include "ConnectManager.h"
#include "game_functions.h"
#include "Object.h"
#include "Player.h"
#include "ResMng.h"
#include "menuitem.h"

class GameFuncs
{
public:
	hgeCallback frame_func();
	hgeCallback render_func();
	static GameFuncs* GetInstance();
private:
	void Disconnect();
	void Game();
	string menu = "main_menu";
	string ip = "192.168.1.48";
	hgeGUI* gui = ResMng::GetInstance()->GetGui();
	hgeGUI* gui_connect = ResMng::GetInstance()->GetGuiConnect();
	std::list<Object*> gObjectList = {};
	HGE* hge = ResMng::GetInstance()->GetHge();
	int lastid = 0;
	int id	= -1;
};

