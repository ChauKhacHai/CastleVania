#include "Camera.h"
#include"Simon.h"

CCamera::CCamera(void)
{
	m_pos = D3DXVECTOR2(0,200);
	
	deadzone.left = 0;
	deadzone.right = SCREEN_WIDTH/2;
	deadzone.bottom =  SCREEN_HEIGHT * 10 / 12;
	deadzone.top =0;
}

void CCamera::setlimit(RECT lm)
{
	limit = lm;
}
void CCamera::setdeadzone(RECT dz)
{
	deadzone = dz; 
}
D3DXVECTOR2 CCamera::Getpos()
{
	return m_pos; 
}
RECT CCamera::GetBoundCamera()
{ 
	return deadzone;
}
void CCamera::Update(D3DXVECTOR2 _pos)
{
	float dx = _pos.x - m_pos.x;//
	float dy = m_pos.y -_pos.y;

	if (dx < deadzone.left)
		m_pos.x = _pos.x - deadzone.left;
	else if (dx > deadzone.right)
		m_pos.x = _pos.x - deadzone.right;


	if (dy > deadzone.bottom)
		m_pos.y = _pos.y + deadzone.bottom;
	else if (dy < deadzone.top)
		m_pos.y = _pos.y + deadzone.top;
}

D3DXMATRIX CCamera::Get_ViewPort()
{
	D3DXMatrixIdentity(&m_viewPort);
	D3DXMatrixAffineTransformation(&m_viewPort, 1, &D3DXVECTOR3(0, 0, 0), &D3DXQUATERNION(0, 0, 0, 0), &D3DXVECTOR3((float)-m_pos.x, (float)m_pos.y, 0));
	m_viewPort._22 = -1.0;
	m_viewPort._41 = (-1)*m_pos.x;
	m_viewPort._42 = m_pos.y;
	return m_viewPort;
}
CCamera::~CCamera(void)
{
}

