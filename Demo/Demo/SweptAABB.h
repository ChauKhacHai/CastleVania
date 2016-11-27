#ifndef _SWEPT_AABB_H_
#define _SWEPT_AABB_H_

#include <math.h>
using namespace std;

enum DIR
{
	NONE = 0,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

struct BOX
{
	//đối tượng di chuyển : có vân tốc
	BOX(float _x, float _y, float _w, float _h, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = _vx;
		vy = _vy;
	}

	//đối tượng đứng yên
	BOX(float _x, float _y, float _w, float _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = 0.0f;
		vy = 0.0f;
	}

	// position of top-left corner : vị trí góc bên trái (tọa độ (x,y))
	float x, y;

	// dimensions: kích thước: dài rộng
	float w, h;

	// velocity: vấn tốc x,y
	float vx, vy;
};

//thong tin va chạm trả về
struct COLLISION_INFO
{
	bool _IsCollided;//có va chạm hay không
	float time;//thời gian va chạm ?? 
	float x;//vec tơ phap tuyên
	float y;////vec tơ phap tuyên
	//DIR dir;//hướng va chạm
};

bool AABBCheck(BOX b1, BOX b2);//hàm check đơn giản khi chưa cố vận tốc,  xem nó có nằm đè lên nhau hay không 
bool AABB(BOX b1, BOX b2, float& moveX, float& moveY);
BOX GetSweptBroadphaseBOX(BOX b);//kiểm tra diện rộng nếu không nằm trong vùng diện rộng thì bị loại ra và là ko va chạm
float SweptAABB(BOX b1, BOX b2, float& normalx, float& normaly);//trả về entrytime thời gian va chạm
BOX CalculateVelocity(BOX b1, BOX b2);//sét lại vận tôc nêu là vật di chuyển

#endif




