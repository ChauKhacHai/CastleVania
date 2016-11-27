#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include"Sprite.h"
#include<d3d9.h>
#include<d3dx9.h>
#include"Texture.h"
#include"Input.h"
#include "Camera.h"
#include"SweptAABB.h"

/// thêm cái kiểu enum này để xác định đối tượng
enum IDObject
{
	//add thêm vô
	SIMON,
	BRICKK,

};

class CGameObject{
protected:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_veloc;
	D3DXVECTOR2  m_accel;
	CSprite *m_sprite;
	RECT m_bound;
	IDObject idObject;
	//max
	D3DXVECTOR2 m_maxVelocity;
	D3DXVECTOR2 m_maxAccelemeter;
	//
	D3DXVECTOR2 StartPostion;


public:
	int m_direct;

	CGameObject(void);
	CGameObject(int, D3DXVECTOR2);
	~CGameObject(void);
	virtual void Init();
	virtual void Update(CInput*, float);//update vi tri cua object va sprite tuong ung
	virtual void UpdatePosition(CInput*, float);
	virtual void UpdateAnimation(CInput*, float);
	virtual void UpdateCollison(CInput*, float);//22/11/2013
	virtual void Draw(LPD3DXSPRITE,CCamera *);
	// thêm cái hàm va chạm vô luôn, trả về thông tin va chạm : COLLISION_INFO
	virtual COLLISION_INFO CollisionWith(CGameObject *o,float);
	// fix lại vị trí của vật sau khi va chạm trả về hướng va chạm luôn
	DIR DirAndFixPositionColli(CGameObject *o, COLLISION_INFO resesult);

	//get
	D3DXVECTOR2 GetVelocity() { return m_veloc; }
	D3DXVECTOR2 GetPosition() { return m_pos; }
	BOX GetBound() { return BOX(m_pos.x , m_pos.y , m_sprite->GetSpriteWidth(), m_sprite->GetSpriteHeight(), m_veloc.x, m_veloc.y); }
	
	CSprite* GetSprite(){ return m_sprite; }
	D3DXVECTOR2 GetMaxVelocity() { return m_maxVelocity; }
	D3DXVECTOR2 GetMaxAccelemeter(){ return m_maxAccelemeter; }


	void SetBound();
	void SetBound(RECT *);
	void SetPosition(D3DXVECTOR2 _pos) { m_pos = _pos; }
	void SetVelocity(D3DXVECTOR2 _velocity) { m_veloc = _velocity; }
	void SetPositionX(float _x) { m_pos.x = _x; }
	void SetPositionY(float _y) { m_pos.y = _y; }
	void SetVelocityX(float _vX) { m_veloc.x = _vX; }
	void SetVelocityY(float _vY) { m_veloc.y = _vY; }
	
	// set max
	void SetMaxVelocity(D3DXVECTOR2 _velocity) { m_maxVelocity = _velocity; }
	void SetMaxVelocityX(float _vX) { m_maxVelocity.x = _vX; }
	void SetMaxVelocityY(float _vY) { m_maxVelocity.y = _vY; }
	void SetMaxAcceleration(D3DXVECTOR2 _accleration) { m_maxAccelemeter = _accleration; }
	void SetMaxAccelerationX(float x){ m_maxAccelemeter.x = x; }
	
	void Stop();

};

#endif