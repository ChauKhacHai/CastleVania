#ifndef DXGRAPHIC_H_
#define DXGRAPHIC_H_

#include<d3d9.h>
#include<d3dx9.h>
#include<Windows.h>
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 224

class CGraphic
{
private:
	LPDIRECT3D9 pd3d;
	LPDIRECT3DDEVICE9 pd3device;
	D3DPRESENT_PARAMETERS d3dpp;
public:
	CGraphic();
	~CGraphic();
	int initDevice(HWND);
	LPDIRECT3D9 getPd3d();
	LPDIRECT3DDEVICE9 getPd3device();
	D3DPRESENT_PARAMETERS getD3dpp();

	void releaseDevice();
	void beginRender();
	void endRender();


};

#endif