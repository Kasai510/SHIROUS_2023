#pragma once
#include "BattleObject.h"


class Item :
    public BattleObject
{
protected:
	Vec2 pos;
	Vec2 prev_pos;
	double r = 10;
	double near_r = 200;
	Vec2 speed{ 0,0 };

	bool dead = false;

public:
	Item(Battle* battle, const Vec2& p);

	virtual void update();
	virtual void move();


	virtual void draw();

	bool is_dead() { return dead; }
};

