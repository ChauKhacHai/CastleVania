#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "Input.h"
class CCamera
{
private:
	D3DXMATRIX m_viewPort;
	D3DXVECTOR2 m_pos;
	RECT deadzone;
	RECT limit;

public:
	CCamera(void);
	~CCamera(void);
	void Update(D3DXVECTOR2);
	void setlimit(RECT);
	void setdeadzone(RECT);
	D3DXVECTOR2 Getpos();
	D3DXMATRIX Get_ViewPort();
	RECT GetBoundCamera();
};

#endif


