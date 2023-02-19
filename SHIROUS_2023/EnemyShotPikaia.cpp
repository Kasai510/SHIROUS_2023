#include "stdafx.h"
#include "EnemyShotPikaia.h"
#include"Battle.h"

EnemyShotPikaia::EnemyShotPikaia(Battle* battle, const Vec2 p):EnemyShot(battle,p)
{
	image_size_int = 250;
	angle = calc_angle();
	mode_stop = true;
	v = { 0, 0 };
	time.restart();
	hit_box_origin = Ellipse{ 0,0,100,20 }.asPolygon();
}

double EnemyShotPikaia::calc_angle()
{
	Vec2 r = battle->get_player().get_pos() - pos;
	return atan2(r.y, r.x);
}

void EnemyShotPikaia::update()
{
	if (mode_stop && time > 0.6s) {
		mode_stop = false;
		v += Vec2{ cos(angle),sin(angle) }*20;
	}

	if (mode_stop) {
		angle = calc_angle();
	}
	else{
		v += Vec2{ cos(angle),sin(angle)} * 1;
	}
	move();
	hit_box = hit_box_origin.rotated(angle).movedBy(pos);
	over=not battle->get_camera().in_camera(hit_box);

	for (auto& stage_object : battle->get_stages())
	{
		if (hit_box.intersects(stage_object.get_rect()))
		{
			over = true;
		}
	}
}

void EnemyShotPikaia::draw()
{
	myCamera& camera = battle->get_camera();
	camera.draw_texture_rotated(TextureAsset(U"pikaia_shot").resized(image_size_int),pos,angle - Math::Pi);
	//camera.draw_texture(hit_box, Palette::Yellow);
}
