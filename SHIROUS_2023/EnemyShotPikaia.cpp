#include "stdafx.h"
#include "EnemyShotPikaia.h"
#include"Battle.h"
#include"Fish.h"
#include"myIEffectBubble.h"
#include"myIEffectAdditiveBlendRect.h"

EnemyShotPikaia::EnemyShotPikaia(Battle* battle, const Vec2& p):EnemyShot(battle,p)
{
	image_size_int = 250;
	angle = calc_angle();
	mode_stop = true;
	draw_edge = true;
	v = { 0, 0 };
	hit_box_origins << Ellipse{ 0,0,100,20 }.asPolygon();
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
		if (time == 6)draw_edge = false;
		if (time == 12)draw_edge = true;
		if (time == 18)draw_edge = false;
		Vec2 angle_nv = Vec2{ cos(angle),sin(angle) };
		Vec2 cross = { angle_nv.y,-angle_nv.x };
		Vec2 out_p1 = -angle_nv * 80 + cross * 20;
		Vec2 out_p2 = -angle_nv * 80 - cross * 20;
		if (time%2==0) {
			battle->get_effects() << std::make_unique<myIEffectBubble>(battle, pos + out_p1, -angle_nv * 20 + RandomVec2() * 5, Random() * 5);
			battle->get_effects() << std::make_unique<myIEffectBubble>(battle, pos + out_p2, -angle_nv * 20 + RandomVec2() * 5, Random() * 5);
		}
	}
	else{
		Vec2 angle_nv = Vec2{ cos(angle),sin(angle) };
		v += angle_nv * 1;
		battle->get_effects() << std::make_unique<myIEffectBubble>(battle, pos - angle_nv*50 + RandomVec2() * Random() * 30, Random() * 10);

		if (time % 6 == 0)battle->get_items() << std::make_shared<ItemLP>(battle, get_pos(), 10);
	}
	move();
	hit_boxs = hit_box_origins.rotated(angle).movedBy(pos);

	bool dead = false;
	if (battle->get_player().get_rect().intersects(hit_boxs)) {
		battle->get_player().damage(30);
		dead = true;
		over = true;
	}
	if (not battle->get_camera().in_camera(hit_boxs)) {
		over = true;
	}
	for (auto& stage_object : battle->get_stages())
	{
		if (hit_boxs.intersects(stage_object.get_rect()))
		{

			dead = true;
			over = true;
		}
	}
	if (dead) {
		for (size_t i : step(10)) {
			battle->get_effects() << std::make_unique<myIEffectAdditiveBlendRect>(battle,RandomVec2(hit_boxs.computeBoundingRect().scaled(0.7)), Vec2(Random(50, 70), Random(50, 70)), Color(50, 150, Random<int>(128, 255), 200));
		}
	}
	time++;
}

void EnemyShotPikaia::draw()
{
	myCamera& camera = battle->get_camera();
	if (draw_edge) {
		{
			ScopedColorMul2D ca{ Palette::Yellow };
			camera.draw_texture(TextureAsset(U"pikaia_shot_white").resized(image_size_int).rotated(angle - Math::Pi), pos);
		}
		ScopedColorAdd2D ca{Color(50,50,0,0)};
		camera.draw_texture(TextureAsset(U"pikaia_shot").resized(image_size_int).rotated(angle - Math::Pi), pos);

	}
	else {
		camera.draw_texture(TextureAsset(U"pikaia_shot").resized(image_size_int).rotated(angle - Math::Pi), pos );
	}
	
	//camera.draw_texture(hit_boxs, Palette::Yellow);
}
