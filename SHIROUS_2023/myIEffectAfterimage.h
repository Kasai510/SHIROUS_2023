#pragma once
#include"myIEffect.h"

class myIEffectAfterimage :
	public myIEffect
{
public:
	myIEffectAfterimage(Battle* battle, const Vec2& p,const TexturedQuad& tex, const Color& color);
	void update();
	void draw();
private:
	Vec2 p;

	TexturedQuad tex;
	Color color;
	int life = 0;
};

