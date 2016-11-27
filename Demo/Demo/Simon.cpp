#include"Simon.h"
#include <stdlib.h>
#include"SweptAABB.h"
Simon::Simon()
{
	idObject = IDObject::SIMON;
	Init();
}

Simon::~Simon(){
}
void Simon::Init(){
	m_pos = D3DXVECTOR2(50, 0);
	m_veloc = D3DXVECTOR2(0, 0);
	m_maxVelocity = D3DXVECTOR2(40.0f, 50.0f);
	m_MaxVeloc = m_maxVelocity;
	m_action = run;
	m_direct = 1;
	m_lastPos = D3DXVECTOR2(0, 0);
	m_simon = CResourceManager::GetInstance()->GetResouce(SIMON_RUN_ID);
	m_simon_attack = CResourceManager::GetInstance()->GetResouce(SIMON_ATTACK_ID);
	m_sprite = m_simon;
	CGameObject::SetBound();

}


void Simon::UpdateAnimation(CInput *m_input, float _time){
	m_sprite = m_simon;
	if (m_veloc.x == 0 && m_veloc.y == 0)//normal
	{
		if (m_direct == 1){
			m_sprite->SetCurrentSprite(4);
			m_sprite->UpdateSprite();
		}
		if (m_direct == -1){
			m_sprite->SetCurrentSprite(3);
			m_sprite->UpdateSprite();
		}
	}
	if (m_veloc.y != 0)
	{
		if (m_action == Jump)
		{
			m_sprite->SetCurrentSprite(0);
			m_sprite->UpdateSprite();
		}
	}
	if (m_veloc.x != 0 && m_veloc.y == 0 && m_action != down){//run
		if (m_direct == 1){
			m_sprite->SetTimeAmination(TIMEAMINATION);
			m_sprite->UpdateSprite(_time, 5, 6, 1);
		}
		if (m_direct == -1){

			m_sprite->SetTimeAmination(TIMEAMINATION);
			m_sprite->UpdateSprite(_time, 2, 3, -1);
		}
	}


	if (m_action == Jump){//jump
		if (m_direct == 1){
			m_sprite->SetCurrentSprite(7);
			m_sprite->UpdateSprite();
		}
		if (m_direct == -1){

			m_sprite->SetCurrentSprite(0);
			m_sprite->UpdateSprite();
		}
	}
	if (m_action == attack){//attack
		m_sprite = m_simon_attack;
			if (m_direct == 1){
				m_sprite->SetTimeAmination(TIMEAMINATION);
				m_sprite->UpdateSprite(_time, 3, 5, 1);
				if (m_sprite->GetCurrentSprite() == 5)
				{
					attackTimes++;
					attackTimes %= 3;
					if (attackTimes ==0 )
					{
						m_action = normal;
					}
				}
			}
			else
			if (m_direct == -1){
				m_sprite->SetTimeAmination(TIMEAMINATION);
				m_sprite->UpdateSprite(_time, 0, 2, -1);
				if (m_sprite->GetCurrentSprite() == 2)
				{
					attackTimes++;
					attackTimes %= 3;
					if (attackTimes == 0)
					{
						m_action = normal;
					}
				}
			}	
	}
	if (m_action == down && m_veloc.x == 0 && m_veloc.y == 0){//down
		if (m_direct == 1){
			m_sprite->SetCurrentSprite(7);
			m_sprite->SetTimeAmination(0);
			m_sprite->UpdateSprite();
		}
		if (m_direct == -1){

			m_sprite->SetCurrentSprite(0);
			m_sprite->SetTimeAmination(0);
			m_sprite->UpdateSprite();
		}
	}
}
void Simon::UpdatePosition(CInput *m_input, float _time){
	if (m_input->OnKeyUp(DIK_RIGHT)){
		switch (m_action)
		{
		case down :
			m_action = normal;
			break;
		case Jump :
			m_action = normal;
			m_pos.y = m_lastPos.y;
			break;
		
		default:
			m_veloc.x = 0;
			break;
		}
	}
	if (m_input->IsKeyDown(DIK_RIGHT) && m_action != down)
	{
		m_direct = 1;
		m_veloc.x = m_maxVelocity.x;
	}
	else if (m_input->IsKeyDown(DIK_LEFT) && m_action != down)
	{
		m_direct = -1;
		m_veloc.x = -m_maxVelocity.x ;
	}
	else if (m_input->IsKeyDown(DIK_DOWN) && m_action != Jump)
	{
		m_action = down;
		m_veloc.x = 0;
		m_veloc.y = 0;
	}
	else
	{
		if (m_veloc.x != 0){
			m_accel.x = -1.0f*m_direct*(m_maxAccelemeter.x);
		}
		if ((m_direct*m_veloc.x) <= 0){
			m_veloc.x = 0;
			
		}

	}
	if (m_input->IsKeyDown(DIK_V)){
		m_lastPos.y = m_pos.y;
		if (m_veloc.y == 0 && m_action == normal){
			m_action = Jump;
			m_veloc.y = -m_MaxVeloc.y;
		}

	}
	else if (m_input->IsKeyPress(DIK_C))
	{
		m_action = attack;
		m_veloc.x = 0;
		m_veloc.y = 0;

	}
	CGameObject::UpdatePosition(m_input, _time);

}

void Simon::UpdateCollison(CInput *m_input, float _time)
{
	if (m_pos.y < 40){
		m_pos.y = 40;
		m_accel.y = 0;
		m_veloc.y = 0;
		m_action = normal;
	}
	else if (m_pos.y > 0){

	}
}