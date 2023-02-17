#include"Shot.h"
#include"Battle.h"


Shot::Shot(Battle* battle,Vec2 p)
{
	this->battle = battle;
	pos = p;
}

Shot::Shot(Battle* battle, Fish* master)
{
	this->battle = battle;
	this->master = master;
}

void Shot::update()
{
	move();
}
void Shot::move()
{
	pos.x += 10;
}
RectF Shot::get_hitbox()
{
	return RectF(Arg::center(pos), width, height);
}

Circle Shot::get_hitcircle()
{
	return Circle(Arg::center(pos), width/2);
}

void Shot::draw()
{
	get_hitbox().movedBy(-battle->get_camera().get_center()).scaledAt({ 0,0 }, battle->get_camera().get_scale()).movedBy(Scene::CenterF()).draw(Palette::Red);
}

