#pragma once
#include "myIEffect.h"
class myIEffectClash :
    public myIEffect
{
public:
	myIEffectClash(class Battle* battle, const Vec2& p, const double max_r = 30,Color c = HSV(1, 1, 1, 0.7));
	myIEffectClash(class Battle* battle, const Vec2& p,Color c);
	void update();
	void draw();
private:
	double effect_timer{0};
	Vec2 pos{0,0};
	double max_r{0};//最大半径
	Color color;
};

