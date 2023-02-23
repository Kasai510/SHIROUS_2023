#include "stdafx.h"
#include "myIEffectBubble.h"
#include"Battle.h"

myIEffectBubble::myIEffectBubble(class Battle* battle,const Vec2& p, const double r):myIEffect(battle)
{
	this->p = p;
	this->r = r;
	v = { 0,0 };
	life = int(Random() * 60) + 60;//60~120
}

void myIEffectBubble::update()
{
	v = RandomVec2() * Random();
	v.y += -0.2;
	p += v;
	if (time == life) {
		dead = true;
	}
	time++;
}

void myIEffectBubble::draw()
{
	myCamera& c = battle->get_camera();
	c.draw_texture(Circle{ p,r }, Palette::White);
}
