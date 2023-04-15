#include "stdafx.h"
#include "myIEffectAdditiveBlendRect.h"
#include"Battle.h"


myIEffectAdditiveBlendRect::myIEffectAdditiveBlendRect(class Battle* battle, const Vec2& p, const Vec2& s, Color color) :myIEffect(battle)
{
	this->p = p;
	this->s = s;
	this->color = color;
	v = { 0,0 };
	life = Random<int>(60, 120);
}

myIEffectAdditiveBlendRect::myIEffectAdditiveBlendRect(Battle* battle, const Vec2& p, const Vec2& v, const Vec2& s, Color color) :myIEffect(battle)
{
	this->p = p;
	this->s = s;
	this->color = color;
	this->v = v;
	life = Random<int>(60, 120);
}

void myIEffectAdditiveBlendRect::update()
{
	v += RandomVec2() * Random() * 0.5;
	v.y += -0.02;
	v *= 0.9;
	p += v;
	if (time == life) {
		dead = true;
	}
	time++;
}

void myIEffectAdditiveBlendRect::draw()
{
	myCamera& c = battle->get_camera();
	ScopedRenderStates2D srs{ BlendState::Additive };
	c.draw_texture(RectF{ p,s }, color);
}
