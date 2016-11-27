#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
#include <stdio.h>
#pragma warning(disable:4996)
#define VIEWPORTSIZETILE =  32
class Background
{
	LPDIRECT3DTEXTURE9 m_texture;
	D3DXVECTOR2 m_pos;
	D3DCOLOR ColorKey;
	float m_speed;
	D3DXVECTOR3** _CoorTile;
public:
	Background();
	~Background();
	/*D3DXVECTOR2 getpos(){ return m_pos; };
	float getspeed() { return m_speed; };	*/
	void InitCoordinates();
	/*void setcolorkey(D3DCOLOR);
	void setpos(D3DXVECTOR2 pos);
	void setspeed(float speed);*/
	void Init(LPDIRECT3DTEXTURE9, char*);
	void Draw(LPD3DXSPRITE _spriteHandler, D3DXVECTOR2 v_obj, int _lobeginx, int _lcendx,int _lobeginy, int _lcendy);
private:
	
	int heighttile ;
	int widthtile ;
	int tile_sizex ;
	int tile_sizey ;
	int w_sizex ;
	int w_sizey ;
	int numbertilecol ;
	int numbertilerow ;
	int total ;
	int** map;
	int gOffset;
	bool inited = false;
	int view;
	int old_c=0;
};

