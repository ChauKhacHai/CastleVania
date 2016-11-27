#include "CWindown.h"
#include "DxGraphics.h"
#include "Timer.h"
#include "Input.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Brick.h"
#include "Simon.h"
#include "Surface.h"
#include"colision.h"

#include "Background.h"
#include <string>
#include <sstream>
#include <iostream>



class CGameApp{

private:
	CCamera *camera;
	CWindown *windown;
	CGraphic *graphic;
	CInput *m_input;
	CCamera *m_camera;
	CTimer *m_time;
	Simon *simon;
	CBrick **m_brick;
	ID3DXFont *m_font;

	Background *level3, *level4;

	int FPS;
	float Deltal;//thoi gian update game


public:

	LPD3DXSPRITE m_spriteHandler;
	LPDIRECT3DDEVICE9 m_lpDirect3DDevice;
	CGameApp();
	~CGameApp();
	int gameInit(HINSTANCE);
	int gameRun();
	int gameEnd();

	void updateWorld(float);
	void drawWorld();
	void DisplaySomeText(LPCSTR text)
	{
		
		// Create a colour for the text - in this case blue
		D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 0, 0, 255);

		// Create a rectangle to indicate where on the screen it should be drawn
		RECT rct;
		rct.left = 2;
		rct.right = 780;
		rct.top = 10;
		rct.bottom = rct.top + 20;

		// Draw some text 
		// Create a D3DX font object
		
		//m_font->DrawText(NULL, text, -1, &rct, 0, fontColor);

	}
};
