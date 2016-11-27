#ifndef CSPRITE_H_
#define CSPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>
class CSprite
{
protected:
	LPDIRECT3DTEXTURE9 m_texture;
	RECT rect;
	int m_curSprite;
	int m_totalSprite;
	int m_columnSprite;
	int m_widthSprite;
	int m_heightSprite;
	float m_timeAmination;
	float m_timeCurrent;
public:
	CSprite();
	CSprite(int _total, int _column, int _widthtext, int _heighttext);
	~CSprite();
	void Init(LPDIRECT3DTEXTURE9);
	void PositionSprite();
	void UpdateSprite();
	void UpdateSprite(float, int, int, int);
	void UpdateSprite2(float, int, int, int);
	void DrawSprite(LPD3DXSPRITE, D3DXVECTOR2);
	//set
	void SetCurrentSprite(int _cursprite){ m_curSprite = _cursprite; }
	void SetTimeAmination(float _time){ m_timeAmination = _time; }
	//get
	float GetSpriteWidth(){ return (float)m_widthSprite; }
	float GetSpriteHeight(){ return (float)m_heightSprite; }
	int GetCurrentSprite(){ return m_curSprite; }
};

#endif


