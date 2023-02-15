#include"Player_shot.h"

Player_shot::Player_shot(Vec2 p)
{
	name = U"イワシ";
	pos = p;
}
Player_shot::Player_shot(String n, Vec2 p)
{
	name = n;
	pos = p;
}

void Player_shot::update()
{
	move();
}
void Player_shot::move()
{
	pos.x += 10;
}
RectF Player_shot::get_hitbox()
{
	return RectF(Arg::center(pos), width, height);
}

void Player_shot::draw(myCamera camera)
{
	get_hitbox().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).draw(Palette::Red);
}

