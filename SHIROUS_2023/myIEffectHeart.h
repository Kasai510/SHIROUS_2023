#pragma once
#include "myIEffect.h"
class myIEffectHeart :
    public myIEffect
{
public:
	myIEffectHeart(class Battle* battle, const Vec2& p, const double r);
	myIEffectHeart(class Battle* battle, const Vec2& p, const Vec2& v, const double r);
	void update();
	void draw();
private:
	Vec2 p;
	Vec2 v;
	double r;
	int life;
};

