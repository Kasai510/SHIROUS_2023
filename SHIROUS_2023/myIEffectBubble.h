#pragma once
#include "myIEffect.h"
class myIEffectBubble :
    public myIEffect
{
public:
	myIEffectBubble(class Battle* battle,const Vec2& p,const double r,Color c = Palette::White);
	void update();
	void draw();
private:
	Vec2 p;
	Vec2 v;
	double r;
	int life;
	Color color;
};

