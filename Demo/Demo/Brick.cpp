#include"Brick.h"
CBrick::CBrick(){
	m_pos = D3DXVECTOR2(25, 25);
	Init();
}
CBrick::CBrick(int _id, D3DXVECTOR2 pos){
	idObject = IDObject::BRICKK;
	m_pos = pos;
	Init();
}
void CBrick::Init(){
	//CGameObject::Init();
	
	
}

void CBrick::UpdateAnimation(CInput *_input, float _time){
	m_sprite->SetCurrentSprite(0);
	m_sprite->SetTimeAmination(0);
	m_sprite->UpdateSprite();
}

CBrick::~CBrick(){}

