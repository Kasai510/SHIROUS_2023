#pragma once
#include "Fish.h"
class Enemy :
	public Fish//,public std::enable_shared_from_this<Enemy>
{
public:
	Enemy(Battle* battle,Vec2 p);
	void update();
	void draw();
	void move();
	void damage(double d);
protected:
	double hp = 50;
	int time = 0;
};

