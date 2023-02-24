#pragma once
#include "myIEffect.h"
class myIEffectClash :
    public myIEffect
{
public:
	myIEffectClash(class Battle* battle, const Vec2& p, const double max_r = 30, Color c = Palette::White);
	void update();
	void draw();
private:
	double effect_timer;
	Vec2 pos;
	double max_r;//最大半径
	Color color;
};

