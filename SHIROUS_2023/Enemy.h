#pragma once
#include "Fish.h"
class Enemy :
	public Fish//,public std::enable_shared_from_this<Enemy>
{
public:
	Enemy(Battle* battle,const Vec2& p);
	void update();
	void draw();
	void move();
protected:
	int time = 0;
};

