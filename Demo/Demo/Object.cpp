#include"Object.h"



CGameObject::CGameObject(){
	m_pos = D3DXVECTOR2(0, 0);
	Init();
}
CGameObject::CGameObject(int _id, D3DXVECTOR2 _mpos){
	//idObject = null;
	m_pos = _mpos;
	Init();
}
CGameObject::~CGameObject(){}
void CGameObject::Init(){

	m_veloc = D3DXVECTOR2(0, 0);
	StartPostion = m_pos;
}
void CGameObject::SetBound(){
	m_bound.left = (LONG)(m_pos.x /*- m_sprite->GetSpriteWidth() / 2*/);
	m_bound.bottom = (LONG)(m_pos.y /*- m_sprite->GetSpriteHeight() / 2*/);
	m_bound.right = (LONG)(m_bound.left + m_sprite->GetSpriteWidth());
	m_bound.top = (LONG)(m_bound.bottom + m_sprite->GetSpriteHeight());


}
void CGameObject::SetBound(RECT *r){
	m_bound.left = (LONG)r->left;//(LONG)m_pos.x - m_sprite->GetSpriteWidth()/2;
	m_bound.bottom = (LONG)r->bottom;// (LONG)m_pos.y - m_sprite->GetSpriteHeight()/2;
	m_bound.right = (LONG)r->right;//(LONG)(m_bound.left + m_sprite->GetSpriteWidth());
	m_bound.top = (LONG)r->top;//(LONG)(m_bound.bottom + m_sprite->GetSpriteHeight());
}


COLLISION_INFO CGameObject::CollisionWith(CGameObject *o, float time)
{
	COLLISION_INFO result;
	result.time = 0;

	/// nếu kết thúc màn .... thì ko kiểm tra nữa
	/*if (_Live_State == DESTROYED || o->_Live_State == DESTROYED || _Live_State == DYING || o->_Live_State == DYING)
	{
	result._IsCollided = false;
	return result;
	}*/

	BOX b1 = this->GetBound();
	BOX b2 = o->GetBound();
	result._IsCollided = AABB(b1, b2, result.x, result.y);//kiểm tra va cham khi chưa có vân tốc (lúc đầu khởi tạo)
	if (result._IsCollided) return result;
	b1 = CalculateVelocity(b1, b2);
	// đưa vào vùng diện rộng của b1 và xét b2 có nằm trong đó hay không
	if (AABBCheck(GetSweptBroadphaseBOX(b1), b2))
	{
		result.time = SweptAABB(b1, b2, result.x, result.y);

		//nếu như có va chạm xảy ra.
		if (result.time < time)
		{
			result._IsCollided = true;
			return  result;
		}
		else
		{
			result._IsCollided = false;
			return result;
		}
	}
	else
	{
		result._IsCollided = false;
		return result;
	}
	return result;
}

DIR CGameObject::DirAndFixPositionColli(CGameObject *o, COLLISION_INFO result)
{
	BOX b1 = this->GetBound();
	BOX b2 = o->GetBound();

	//if ((b1.bottom == _Object->getBound().top && _DynamicObject->getBound().right == _Object->getBound().left)
	//	|| (_DynamicObject->getBound().bottom == _Object->getBound().top && _DynamicObject->getBound().left == _Object->getBound().right))
	//	return IDDirection::DIR_NONE;

	if ((b1.y == b2.y + b2.h && b1.x + b1.w == b2.x)
		|| (b1.y == b2.y + b2.h && b1.x == b2.x + b2.w))
		return DIR::NONE;

	if (result.x < 0 && result.y == 0 && b1.vx > 0)
	{
		//this->SetVelocityX(0);
		this->m_pos.x = b2.x - b1.w;
		return DIR::LEFT;

	}

	if (result.x > 0 && result.y == 0 && b1.vx < 0)
	{
		//this->SetVelocityX(0);
		this->m_pos.x = b2.x + b2.w;
		return DIR::RIGHT;
	}

	if (result.x == 0 && result.y >= 1.0f && b1.vy <= 0)
	{
		//_Vy = 0;
		this->m_pos.y = b2.y + b2.h;
		return DIR::TOP;
	}

	if (result.x == 0 && result.y <= -1.0f && b1.vy > 0)
	{
		//_Vy = 0;
		this->m_pos.y = b2.y - b1.h+15;
		return DIR::BOTTOM;
	}
	return DIR::NONE;
}

void CGameObject::UpdatePosition(CInput *m_input, float _time){
	m_pos += m_veloc * _time;
	SetBound();
}
void CGameObject::Update(CInput *m_input, float _time){
	UpdateCollison(m_input, _time);
	UpdateAnimation(m_input, _time);
	UpdatePosition(m_input, _time);
}

void CGameObject::Draw(LPD3DXSPRITE _spriteHandler, CCamera* camera){
	D3DXMATRIX Scale;
	D3DXMatrixIdentity(&Scale);
	D3DXMatrixTransformation2D(&Scale, &D3DXVECTOR2(m_pos.x, m_pos.y), 0.0f, &D3DXVECTOR2(1.f, -1.f), NULL, 0.f, NULL);
	D3DXMatrixMultiply(&Scale, &Scale, &camera->Get_ViewPort());
	_spriteHandler->SetTransform(&Scale);
	m_sprite->DrawSprite(_spriteHandler, D3DXVECTOR2(m_pos.x, m_pos.y));
}
void CGameObject::UpdateAnimation(CInput *m_input, float _time)
{

}

void CGameObject::UpdateCollison(CInput *m_input, float _time)
{

}

void CGameObject::Stop()
{
	SetVelocity(D3DXVECTOR2(0, 0));
	//SetAcceleration(D3DXVECTOR2(0, 0));
	SetMaxAcceleration(D3DXVECTOR2(0, 0));
	SetMaxVelocity(D3DXVECTOR2(0, 0));
}


