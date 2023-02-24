#include "stdafx.h"
#include "EnemyShotPikaia.h"
#include"Battle.h"
#include"Fish.h"
#include"myIEffectBubble.h"

EnemyShotPikaia::EnemyShotPikaia(Battle* battle, const Vec2 p):EnemyShot(battle,p)
{
	image_size_int = 250;
	angle = calc_angle();
	mode_stop = true;
	v = { 0, 0 };
	hit_box_origin = Ellipse{ 0,0,100,20 }.asPolygon();
}

double EnemyShotPikaia::calc_angle()
{
	Vec2 r = battle->get_player().get_pos() - pos;
	return atan2(r.y, r.x);
}

void EnemyShotPikaia::update()
{
	
	if (mode_stop && time > 36) {
		mode_stop = false;
		v += Vec2{ cos(angle),sin(angle) }*20;
	}

	if (mode_stop) {
		angle = calc_angle();
	}
	else{
		v += Vec2{ cos(angle),sin(angle)} * 1;
		battle->get_effects() << std::make_unique<myIEffectBubble>(battle, pos + RandomVec2() * Random() * 30, Random() * 10);

	}
	move();
	for (int i : step(hit_boxs.size())) {
		update_hit_box(i, pos,angle);
	}

	
	if (battle->get_player().get_rect().intersects(hit_boxs)) {
		battle->get_player().damage(30);
		over = true;
	}
	if (not battle->get_camera().in_camera(hit_boxs)) {
		over = true;
	}
	for (auto& stage_object : battle->get_stages())
	{
		if (hit_boxs.intersects(stage_object.get_rect()))
		{
			over = true;
		}
	}
	time++;
}

void EnemyShotPikaia::draw()
{
	myCamera& camera = battle->get_camera();
	camera.draw_texture(TextureAsset(U"pikaia_shot").resized(image_size_int).rotated(angle - Math::Pi), pos );
	//camera.draw_texture(hit_box, Palette::Yellow);
}
