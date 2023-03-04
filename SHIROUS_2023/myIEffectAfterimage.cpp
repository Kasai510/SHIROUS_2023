#include "stdafx.h"
#include "myIEffectAfterimage.h"
#include"Battle.h"

myIEffectAfterimage::myIEffectAfterimage(Battle* battle, const Vec2& p, const TexturedQuad& tex,const Color& color,int life):myIEffect(battle)
{
	this->p = p;
	this->tex = tex;
	this->color = color;
	this->life = life;
}

void myIEffectAfterimage
::update()
{
	if (time == life) {
		dead = true;
	}
	time++;
}

void myIEffectAfterimage::draw()
{
	ScopedColorMul2D scm{ Color(color.r,color.g,color.b,(life-time)*200/(double)life) };
	battle->get_camera().draw_texture(tex, p);
}
