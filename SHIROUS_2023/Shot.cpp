#include"Shot.h"
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
	hit_box = hit_box_origin.moveBy(pos);
}
void Shot::move()
{
	pos.x += 10;
}

Polygon Shot::get_hitbox()
{
	return hit_box;
}


void Shot::draw()
{
	get_hitbox().movedBy(-battle->get_camera().get_center()).scaledAt({ 0,0 }, battle->get_camera().get_scale()).movedBy(Scene::CenterF()).draw(Palette::Red);
}

