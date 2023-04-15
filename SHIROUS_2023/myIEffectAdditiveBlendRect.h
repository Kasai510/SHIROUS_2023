#pragma once
#include "myIEffect.h"
class  myIEffectAdditiveBlendRect:
    public myIEffect
{
public:
	myIEffectAdditiveBlendRect(class Battle* battle, const Vec2& p, const Vec2& s, Color c = Palette::White);
	myIEffectAdditiveBlendRect(class Battle* battle, const Vec2& p, const Vec2& v, const Vec2& s, Color c = Palette::White);
	void update();
	void draw();
private:
	Vec2 p;
	Vec2 v;
	Vec2 s;
	int life;
	Color color;
};

