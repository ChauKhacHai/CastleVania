#include "Texture.h"


CTexture::CTexture(void)
{
}
CTexture::CTexture(LPDIRECT3DDEVICE9 _pd3device)
{
	m_pd3device = _pd3device;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture(string _filename)
{
	HRESULT result;
	result = D3DXGetImageInfoFromFile(_filename.c_str(), &m_info);
	if (FAILED(result))
	{
		return NULL;
	}
	result = D3DXCreateTextureFromFileEx(m_pd3device, _filename.c_str(), m_info.Width, m_info.Height, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), &m_info, NULL, &m_texture);
	if (FAILED(result))
	{
		return NULL;
	}
	return m_texture;
}

D3DXIMAGE_INFO CTexture::GetTextureInfo()
{
	return m_info;
}

CTexture::~CTexture(void)
{
}
