#include "OptionShot.h"
#include"Battle.h"

OptionShot::OptionShot(Battle* battle,Vec2 p)
	: Shot(battle,p)
{

}

OptionShot::OptionShot(Battle* battle, const std::shared_ptr<class Fish>& master)
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
	battle->get_camera().draw_texture(hit_boxs, Palette::Gray);
}
