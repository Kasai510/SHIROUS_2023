#pragma once
#include "Shot.h"
class EnemyShot :
	public Shot
{
public:
	EnemyShot(Battle* battle, const Vec2& p);
	void move();
protected:
	Vec2 v{ -10,0 };
};

