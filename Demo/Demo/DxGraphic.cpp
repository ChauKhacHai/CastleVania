#include "DxGraphics.h"


CGraphic::CGraphic(void)
{
	pd3d = NULL;
	pd3device = NULL;
}

int CGraphic::initDevice(HWND _wndHandle)
{
	if (NULL == (pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return 0;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.hDeviceWindow = _wndHandle;
	if (FAILED(pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _wndHandle,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pd3device)))
	{
		if (FAILED(pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _wndHandle,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &pd3device)))
		{
			if (FAILED(pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_SW, _wndHandle,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &pd3device)))
			{
				return 0;
			}
		}
	}
	return 1;
}
LPDIRECT3D9 CGraphic::getPd3d()
{
	return pd3d;
}
LPDIRECT3DDEVICE9 CGraphic::getPd3device()
{
	return pd3device;
}
D3DPRESENT_PARAMETERS CGraphic::getD3dpp()
{
	return d3dpp;
}
void CGraphic::beginRender()
{

	if (pd3device != NULL)
	{
		pd3device->BeginScene();
		pd3device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(51, 102, 255), 1.0f, 0);
	}
}
void CGraphic::endRender()
{
	pd3device->EndScene();
	pd3device->Present(NULL, NULL, NULL, NULL);
}
void CGraphic::releaseDevice()
{
	if (pd3d != NULL)
	{
		pd3d->Release();
		pd3d = NULL;
	}
	if (pd3device != NULL)
	{
		pd3device->Release();
		pd3device = NULL;
	}
}
CGraphic::~CGraphic(){}