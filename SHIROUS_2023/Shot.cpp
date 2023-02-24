﻿#include"Shot.h"
#include"Battle.h"


Shot::Shot(Battle* battle,Vec2 p)
{
	this->battle = battle;
	pos = p;
	
}

Shot::Shot(Battle* battle, const std::shared_ptr<class Fish>& master)
{
	this->battle = battle;
	this->master = master;
}



void Shot::update()
{
	move();
	hit_boxs = hit_box_origins.movedBy(pos);
}
void Shot::move()
{
	pos.x += 10;
}

void Shot::update_hit_box(int num, const Vec2& pos, double angle)
{
	hit_boxs[num] = hit_box_origins[num].movedBy(pos).rotated(angle);
}



void Shot::draw()
{
	for (auto& h : hit_boxs) {
		battle->get_camera().draw_texture(h, Palette::Red);
	}
}

