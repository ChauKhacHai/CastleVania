#include "Sprite.h"
#include "ResourceManager.h"
#include "Simon.h"
CSprite::CSprite(void)
{
}
CSprite::CSprite(int _total, int _column, int _widthtext, int _heighttext){
	m_curSprite = 0;
	m_columnSprite = _column;
	m_totalSprite = _total;
	m_widthSprite = _widthtext / _column;
	m_heightSprite = _heighttext / (_total / _column);
	m_timeAmination = 0;
	m_timeCurrent = 0;
}
void CSprite::Init(LPDIRECT3DTEXTURE9 _texture){
	m_texture = _texture;
}
void CSprite::PositionSprite(){
	rect.left = (m_curSprite % m_columnSprite) * m_widthSprite;
	rect.top = (m_curSprite / m_columnSprite) * m_heightSprite;
	rect.right = rect.left + m_widthSprite;
	rect.bottom = rect.top + m_heightSprite;

}
void CSprite::UpdateSprite(){
	PositionSprite();
}
void CSprite::UpdateSprite(float _time, int _spriteBegin, int _SpriteEnd, int _flag){
	if (m_timeAmination != 0){
		if (m_timeCurrent >= m_timeAmination)
		{
			if (_flag == -1)
			{
				m_curSprite--;
				if (m_curSprite < _spriteBegin){
					m_curSprite = _SpriteEnd;
				}
				if (m_curSprite > _SpriteEnd){
					m_curSprite = _SpriteEnd;
				}
			}
			if (_flag == 1)
			{
				m_curSprite++;
				if (m_curSprite < _spriteBegin){
					m_curSprite = _spriteBegin;
				}
				if (m_curSprite > _SpriteEnd){
					m_curSprite = _spriteBegin;
			   
				}
			}
			PositionSprite();
			m_timeCurrent = 0;

		}
		else
		{
			m_timeCurrent += _time;
		}
	}
}
void CSprite::UpdateSprite2(float _time, int _spriteBegin, int _SpriteEnd, int _flag){
	if (m_timeAmination != 0){

	}
}
void CSprite::DrawSprite(LPD3DXSPRITE m_spriteHandle, D3DXVECTOR2 t_pos)
{
	D3DXVECTOR3 position = D3DXVECTOR3(t_pos.x - GetSpriteWidth() / 2, t_pos.y - GetSpriteHeight() / 2, 0);

	m_spriteHandle->Draw(m_texture, &rect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
}
CSprite::~CSprite()
{
}


