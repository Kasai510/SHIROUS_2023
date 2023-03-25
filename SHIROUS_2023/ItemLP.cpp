#include "stdafx.h"
#include "ItemLP.h"
#include"Battle.h"

ItemLP::ItemLP(Battle* battle, const Vec2& p, double lp) :Item(battle, p)
{
	LP = lp;
	r = 10;
	near_r = 500;
	speed = Random(3.0, 7.0) * RandomVec2();
}

void ItemLP::update()
{
	move();
}
void ItemLP::move()
{
	if (!catched && Circle(pos, near_r).intersects(battle->get_player().get_pos()))catched = true;
	if (catched)
	{
		speed += (battle->get_player().get_pos() - pos) / 100.0;
		if ((battle->get_player().get_pos() - pos).length() < 50)
		{
			battle->get_player().add_LP(LP);
			dead = true;
		}
	}

	prev_pos = pos;
	pos += speed;
	speed /= 1.1;
}

void ItemLP::draw()
{
	battle->get_camera().draw_texture(Circle(pos, r), Palette::Lightgreen);
	//battle->get_camera().draw_texture(Circle(pos, near_r), Palette::Lightgreen);
}
