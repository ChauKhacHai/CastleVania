#include "SweptAABB.h"
#include <iostream>
bool AABBCheck(BOX b1, BOX b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y + b1.h < b2.y || b1.y > b2.y + b2.h);
}

// returns true if the BOXes are colliding (velocities are not used)
// moveX and moveY will return the movement the b1 must move to avoid the collision

//trả về true nếu nó va chạm(vân tốc không được sử dụng)
//moveX và moveY sẽ trả về  sự vận động của b1 khi khủy bỏ va chạm
bool AABB(BOX b1, BOX b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y + b1.h);
	float b = (b2.y + b2.h) - b1.y;

	// check that there was a collision
	//kiểm tra xem có va chạm xảy ra hay không
	if (l > 0 || r < 0 || t > 0 || b < 0)
		return false;

	// find the offset of both sides
	//tìm ra giá trị của moveX và moveY
	moveX = abs(l) < r ? l : r;
	moveY = abs(t) < b ? t : b;

	// only use whichever offset is the smallest
	//chỉ lấy về giá trị nhỏ nhất
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

// returns a BOX the spans both a current BOX and the destination BOX
BOX GetSweptBroadphaseBOX(BOX b)
{
	BOX broadphaseBOX(0.0f, 0.0f, 0.0f, 0.0f);

	broadphaseBOX.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphaseBOX.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphaseBOX.w = b.vx > 0 ? b.vx + b.w : b.w - b.vx;
	broadphaseBOX.h = b.vy > 0 ? b.vy + b.h : b.h - b.vy;

	return broadphaseBOX;
}

// performs collision detection on moving BOX b1 and static BOX b2
// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
// getting the new position can be retrieved by BOX.x = BOX.x + BOX.vx * collisiontime
// normalx and normaly return the normal of the collided surface (this can be used to do a response)

//thực hiện va chạm vơi b1 động, b2 tĩnh
//trả về thời gian va chạm(bắt đầu ở 0 và kêt thúc tại 1)
float SweptAABB(BOX b1, BOX b2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
		/*yInvEntry = (b2.y - b2.h) - b1.y;
		yInvExit = b2.y - (b1.y - b1.h);*/
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
		/*yInvEntry = (b1.y - b1.h) - b2.y;
		yInvExit = b1.y - (b2.y - b2.h);*/
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	if (xEntry > 1.0f) xEntry = -std::numeric_limits<float>::infinity();
	if (yEntry > 1.0f) yEntry = -std::numeric_limits<float>::infinity();
	// find the earliest/latest times of collision
	float entryTime = std::fmaxf(xEntry, yEntry);
	float exitTime = std::fminf(xExit, yExit);
	float move_x = 0, move_y = 0;

	// if there was no collision
	if (entryTime > exitTime) return 1.0f;
	if (xEntry < 0.0f && yEntry < 0.0f) return 1.0f;
	if (xEntry > 1.0f || yEntry > 1.0f) return 1.0f;
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

BOX CalculateVelocity(BOX b1, BOX b2)
{
	if (b2.vx == 0 && b2.vy == 0) return b1;
	else
	{
		b1.vx -= b2.vx;
		b1.vy -= b2.vy;
	}
	return b1;
}