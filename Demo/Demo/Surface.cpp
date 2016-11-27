#include "Surface.h"

Surface::Surface()
{
	m_lpBackBuffer = NULL;
	m_lpSurface = 0;
}

Surface::Surface(const Surface & surface)
{
	m_lpSurface = LPDIRECT3DSURFACE9(surface.m_lpSurface);
	m_lpBackBuffer = LPDIRECT3DSURFACE9(surface.m_lpBackBuffer);
}

Surface::~Surface()
{

}

void Surface::LoadSurfaceFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, D3DCOLOR ColorKey, LPCSTR fileName)
{
	D3DXIMAGE_INFO _infoImage;//biến để lưu thông tin của ảnh mang vào
	HRESULT hr;

	//lấy thông tin về ảnh
	hr = D3DXGetImageInfoFromFile(fileName, &_infoImage);

	//kiểm tra
	if (FAILED(hr))
	{
		return;
	}

	hr = _lpDirectDevice->CreateOffscreenPlainSurface(
		_infoImage.Width, //chiều dài
		_infoImage.Height,//chiều cao
		D3DFMT_A8R8G8B8,//chọn format
		D3DPOOL_DEFAULT,// chọn vùng nhớ tự động
		&m_lpSurface,//con trỏ lưu surface được tạo ra ở trên
		0);

	if (FAILED(hr))
	{
		return;
	}

	hr = D3DXLoadSurfaceFromFile(
		m_lpSurface,
		0,
		0,
		fileName,
		0,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,255,255), //là màu chúng ta muốn transparent,
		0);

	if (FAILED(hr))
	{
		return;
	}
	hr = _lpDirectDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_lpBackBuffer);
	if (FAILED(hr))
	{
		return;
	}
}
void Surface::RenderSurface(LPDIRECT3DDEVICE9 _lpDirectDevice, RECT * SourceRect, RECT * DesRect)
{
	//chuyển đổi vẽ lên màn hình
	_lpDirectDevice->StretchRect(
		m_lpSurface,//CON TRỎ surface
		SourceRect,//phần hình cần lấy
		m_lpBackBuffer,//backbuffer
		DesRect,//vị trí đặt
		D3DTEXF_NONE);
}

void Surface::UnLoadSurface()
{

}
