#pragma once
#include <d3dx9.h>

class Surface
{
private:
	LPDIRECT3DSURFACE9 m_lpSurface;//kiểu surface
	LPDIRECT3DSURFACE9 m_lpBackBuffer;
public:
	Surface();
	Surface(const Surface& surface);
	void LoadSurfaceFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice,
		D3DCOLOR ColorKey,//màu chúng ta muốn làm trong suốt
		LPCSTR fileName);
	void RenderSurface(LPDIRECT3DDEVICE9 _lpDirectDevice,//thiết bị đồ họa
		RECT * SourceRect, //phần hình chữ nhật được cắt ra từ tấm hình truyên vào
		RECT* DesRect//địa điểm đặt hình
		);
	void UnLoadSurface();
	~Surface();

};
