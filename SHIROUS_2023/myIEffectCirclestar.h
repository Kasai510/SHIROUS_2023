#pragma once
#include "myIEffect.h"

class myIEffectCirclestar :
    public myIEffect
{
public:
	myIEffectCirclestar(Battle* battle, const Vec2& p, const double r);
	void update();
	void draw();
private:
	Vec2 p;
	double r;
};

