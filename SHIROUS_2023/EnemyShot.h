#pragma once
#include "Shot.h"

class EnemyShot :
	public Shot
{
public:
	EnemyShot(Battle* battle, const Vec2& p);
	EnemyShot(Battle* battle, const Vec2& p,const std::shared_ptr<class Fish>& s_master);
	void update();
	void move();
protected:
	Vec2 v{ -10,0 };
	std::weak_ptr<class Fish> w_master;
	int time = 0;
};

