
#include "CGameApp.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmnd){
	
	CGameApp *gameApp;
	gameApp = new CGameApp();
	if (!gameApp->gameInit(hInstance))
	{
		return 0;
	}

	gameApp->gameRun();
	gameApp->gameEnd();
	return 1;

}


