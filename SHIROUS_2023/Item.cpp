#include "stdafx.h"
#include "Item.h"
#include "Battle.h"


Item::Item(Battle* battle, const Vec2& p) :BattleObject(battle)
{
	pos = p;
	prev_pos = p;
	draw_order = 6;
}

void Item::update()
{
	move();
}
void Item::move()
{
	prev_pos = pos;
	pos += speed;
}

void Item::draw()
{
	battle->get_camera().draw_texture(Circle(pos, r), Palette::White);
}
