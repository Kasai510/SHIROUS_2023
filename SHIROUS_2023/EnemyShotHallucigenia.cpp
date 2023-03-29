#include "stdafx.h"
#include "EnemyShotHallucigenia.h"
#include"Battle.h"
#include"Fish.h"
#include"myIEffectBubble.h"
#include"myIEffectAfterimage.h"

EnemyShotHallucigenia::EnemyShotHallucigenia(Battle* battle, const Vec2& p) :EnemyShot(battle, p)
{
	image_size_int = 200;
	image_angle = 0;
	mode_stop = true;
	v = { 0, 0 };
	hit_box_origins << Circle(0,0,50).asPolygon(8);
}

double EnemyShotHallucigenia::calc_angle()
{
	Vec2 r = battle->get_player().get_pos() - pos;
	return atan2(r.y, r.x);
}

void EnemyShotHallucigenia::update()
{

	if (mode_stop && time > 36) {
		mode_stop = false;
		v += Vec2{ Random(-5,5),-10};
	}

	if (mode_stop) {
		if (time % 2 == 0) {
			battle->get_effects() << std::make_unique<myIEffectBubble>(battle, pos+RandomVec2()*Random(50), Random() * 5);
		}
	}
	else {
		Vec2 r = battle->get_player().get_pos() - pos;
		Vec2 addv = Vec2{ -v.y,v.x }.normalized() * 0.1;
		double z = v.cross(r);
		if (z > 0) {//player is right
			v += addv;
		}
		else {//player is left
			v -= addv;
		}
		battle->get_effects() << std::make_unique<myIEffectBubble>(battle, pos - v.normalized() * 50 + RandomVec2() * Random() * 30, Random() * 10);
		if (time % 10 == 0) {
			battle->get_effects() << std::make_unique<myIEffectAfterimage>(battle, pos, TextureAsset(U"hallucigenia_shot").resized(image_size_int).rotated(image_angle), Color(0, 255, 0),25);
		}
		if(time % 15 == 0 && time < 200)battle->get_items() << std::make_shared<ItemLP>(battle, get_pos(), 10);
	}
	
	image_angle += 0.2;

	move();
	hit_boxs = hit_box_origins.movedBy(pos);


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

void EnemyShotHallucigenia::draw()
{
	myCamera& camera = battle->get_camera();
	//camera.draw_texture(hit_boxs, Palette::Yellow);
	camera.draw_texture(TextureAsset(U"hallucigenia_shot").resized(image_size_int).rotated(image_angle), pos);
	

}
