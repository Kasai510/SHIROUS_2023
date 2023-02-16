#include "OptionShot.h"

OptionShot::OptionShot(Vec2 p) : Shot(p)
{

}


void OptionShot::update()
{
	move();
}
void OptionShot::move()
{
	pos.x += 10;
}

void OptionShot::draw(myCamera camera)
{
	get_hitbox().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).draw(Palette::Gray);
}
