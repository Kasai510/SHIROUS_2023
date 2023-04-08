#include "stdafx.h"
#include "myIEffectHeart.h"
#include"Battle.h"

myIEffectHeart::myIEffectHeart(class Battle* battle, const Vec2& p, const double r) :myIEffect(battle)
{
	this->p = p;
	this->r = r;
	v = { 0,0 };
	life = Random<int>(15, 30);
}

myIEffectHeart::myIEffectHeart(Battle* battle, const Vec2& p, const Vec2& v, const double r) :myIEffect(battle)
{
	this->p = p;
	this->r = r;
	this->v = v;
	life = Random<int>(15, 30);
}

void myIEffectHeart::update()
{
	v += RandomVec2() * Random() * 0.1;
	v.y += -0.02;
	v *= 0.9;
	p += v;
	if (time == life) {
		dead = true;
	}
	time++;
}

void myIEffectHeart::draw()
{
	myCamera& c = battle->get_camera();
	c.draw_texture(TextureAsset(U"heart").resized(2 * r), p);
}
