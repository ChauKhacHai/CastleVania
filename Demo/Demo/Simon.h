
#define VELOCNORMAL  30.0f
#define GROUNDY  95

#include"Object.h"
#include"ResourceManager.h"
#include"Texture.h"
#include"colision.h"
#include"Brick.h"
#define TIMEAMINATION  0.3f
#define MAXHEIGHT  450
enum ActionSimon
{
	normal,
	Jump,
	run,
	down,
	attack
};
class Simon :public CGameObject{
private:

	CSprite *m_simon;
	CSprite *m_simon_attack;
	ActionSimon m_action;	
	D3DXVECTOR2 m_MaxVeloc;//luu tru maxveloc ban dau,khi va cham cho maxvecloc ve 0

	D3DXVECTOR2 m_lastPos;
	
	int keydown;


public:

	Simon();
	~Simon();
	void Init();
	void UpdateAnimation(CInput*, float);	
	void UpdateCollison(CInput*, float);
	void UpdatePosition(CInput*, float);

	void setAction(ActionSimon action){ m_action = action; }
private:
	int attackTimes = 0;
};

	