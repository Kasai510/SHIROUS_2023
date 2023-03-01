#include "stdafx.h"
#include "myIEffectBubble.h"
#include"Battle.h"

myIEffectBubble::myIEffectBubble(class Battle* battle,const Vec2& p, const double r,Color color):myIEffect(battle)
{
	this->p = p;
	this->r = r;
	this->color = color;
	v = { 0,0 };
	life = Random<int>(60, 120);
}

myIEffectBubble::myIEffectBubble(Battle* battle, const Vec2& p, const Vec2& v, const double r, Color color) :myIEffect(battle)
{
	this->p = p;
	this->r = r;
	this->color = color;
	this->v = v;
	life = Random<int>(60, 120);
}

void myIEffectBubble::update()
{
	v += RandomVec2() * Random()*0.5;
	v.y += -0.02;
	v *= 0.9;
	p += v;
	if (time == life) {
		dead = true;
	}
	time++;
}

void myIEffectBubble::draw()
{
	myCamera& c = battle->get_camera();
	ScopedColorMul2D scm{ color };
	c.draw_texture(TextureAsset(U"bubble").resized(2*r), p);
}
