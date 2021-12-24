
#include <cassert>
#include <hge.h>
#include <windows.h>
#include "ConnectManager.h"
#include "ResMng.h"

#pragma comment(lib,"libpthread-static.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)

CRITICAL_SECTION CriticalSection;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	assert(InitializeCriticalSectionAndSpinCount(&CriticalSection,	0x00000400));
	unsigned long threadId;
	void* thread;
	static WSADATA wsaData;
	int wsaerr = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (wsaerr != 0)
	{
		exit(-1);
	}

	ResMng::GetInstance()->GetHge()->System_Start();

	WSACleanup();
	DeleteCriticalSection(&CriticalSection);

	return 0;
}
