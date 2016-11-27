#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
using namespace std;
class CTexture
{
protected:
	D3DXIMAGE_INFO m_info;
	LPDIRECT3DTEXTURE9 m_texture;
	LPDIRECT3DDEVICE9 m_pd3device;
public:
	CTexture(void);
	CTexture(LPDIRECT3DDEVICE9);
	~CTexture(void);
	LPDIRECT3DTEXTURE9 GetTexture(string);
	D3DXIMAGE_INFO GetTextureInfo();
};
#endif