#include "OptionShot.h"
#include"Battle.h"

OptionShot::OptionShot(Battle* battle,Vec2 p)
	: Shot(battle,p)
{

}

OptionShot::OptionShot(Battle* battle,Fish* master)
	: Shot(battle, master)
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

void OptionShot::draw()
{
	//get_hitbox().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).draw(Palette::Gray);
	get_hitbox().movedBy(-battle->get_camera().get_center()).scaledAt({ 0,0 }, battle->get_camera().get_scale()).movedBy(Scene::CenterF()).draw(Palette::Gray);
}
