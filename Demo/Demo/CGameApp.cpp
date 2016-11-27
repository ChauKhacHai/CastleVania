#include "CGameApp.h"

CGameApp::CGameApp(){}

int CGameApp::gameInit(HINSTANCE hIstance){
	windown = new CWindown(hIstance);
	if (!windown->initWindows()){
		return 0;
	}
	graphic = new CGraphic();
	if (!graphic->initDevice(windown->getHandle())){
		return 0;
	}

	D3DXCreateSprite(graphic->getPd3device(), &m_spriteHandler);

	CResourceManager::GetInstance()->Init(graphic->getPd3device(), windown->getHandle());
	if (m_spriteHandler == NULL)
	{
		return 0;
	}

	m_input = new CInput();
	if (!m_input->InitKeyboard(windown->gethInstance(), windown->getHandle()))
	{
		MessageBox(windown->getHandle(), "Can't Create input", "Error", MB_OK);
		return 0;
	}
	m_time = new CTimer();
	FPS = 60;
	simon = new Simon();
	CTexture *m_texture = new CTexture(graphic->getPd3device());
	level3 = new Background();
	level3->Init(m_texture->GetTexture("Level3_tile.png"), "Level3_tile.txt");
	camera = new CCamera();
	D3DXCreateFont(graphic->getPd3device(), 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font);
	return 1;
}

int CGameApp::gameRun(){
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	int done = 0;
	float currentDelta;
	while (!done){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (msg.message == WM_QUIT){
				done = 1;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			currentDelta = m_time->Tick();
			Deltal += currentDelta;
			m_input->ProcessKeyBoard();
			updateWorld(currentDelta);
			if (Deltal > 1.0f / (float)FPS){
				//m_time->FreshTime();
				drawWorld();
				Deltal -= 1.0f / (float)FPS;
				//updateWorld(10.0f / (float)FPS);
			
			}

		}
	}

	return (int)msg.wParam;
}

int CGameApp::gameEnd(){
	return 0;
}

void CGameApp::updateWorld(float time)
{
	simon->Update(m_input, time);
	camera->Update(simon->GetPosition());
}

void CGameApp::drawWorld(){
	graphic->beginRender();
	m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	simon->Draw(m_spriteHandler, camera);
	level3->Draw(m_spriteHandler, simon->GetPosition(), 0, 26, 0, 25);
	
	m_spriteHandler->End();
	graphic->endRender();

}
