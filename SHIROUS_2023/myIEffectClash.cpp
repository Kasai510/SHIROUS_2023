#include "stdafx.h"
#include "myIEffectClash.h"
#include"Battle.h"

myIEffectClash::myIEffectClash(class Battle* battle, const Vec2& p, const double r, Color color) :myIEffect(battle)
{
	this->pos = p;
	this->max_r = r;
	this->color = color;
	time = 0;
}

myIEffectClash::myIEffectClash(class Battle* battle, const Vec2& p, Color color) :myIEffect(battle)
{
	this->pos = p;
	this->max_r = 30;
	this->color = color;
	time = 0;
}

void myIEffectClash::update()
{
	effect_timer += battle->get_scene_del();

	//発生から0.5秒たったら消す
	if (time > 0.5)
	{
		dead = true;
	}
}

void myIEffectClash::draw()
{
	// イージング
	double e = EaseOutExpo(effect_timer);

	myCamera& camera = battle->get_camera();
	Transformer2D tf{ camera.get_mat() };
	Circle{ pos,e * 100 }.drawFrame((max_r * (1.0 - e)), color);
}
