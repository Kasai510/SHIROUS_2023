#include"Shot.h"

Shot::Shot(Vec2 p)
{
	pos = p;
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

void Shot::draw(myCamera camera)
{
	get_hitbox().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).draw(Palette::Red);
}

