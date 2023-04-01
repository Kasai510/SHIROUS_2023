#pragma once
#include "myIEffect.h"

class Fish;

class myIEffectCirclestar :
    public myIEffect
{
public:
	myIEffectCirclestar(Battle* battle, const Vec2& p, const double r,const Color color = Color(255));
	myIEffectCirclestar(Battle* battle, const Vec2& p, const double r, const double dead_frame, const Color color, std::shared_ptr<Fish> master, bool be_following = true);
	void update();
	void draw();
private:
	Vec2 p;
	double r;
	Color color{ Color(255) };
	std::weak_ptr<Fish> master;
	bool be_following{ false };
	double dead_frame{ 30 };//エフェクトが存在するフレーム数
};

