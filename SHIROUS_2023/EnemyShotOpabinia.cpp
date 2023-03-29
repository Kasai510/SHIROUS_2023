#include "stdafx.h"
#include "EnemyShotOpabinia.h"
#include "Battle.h"

EnemyShotOpabinia::EnemyShotOpabinia(Battle* battle, const Vec2& p):EnemyShot(battle,p)
{
	image_size_int = 200;
	hit_box_origins << Circle{ 0,0,30 }.asPolygon();
	v = { -1,0 };
	image_angle = 0;
}

void EnemyShotOpabinia::update()
{
	move();
	hit_boxs = hit_box_origins.movedBy(pos);
	image_angle += 0.03;

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

void EnemyShotOpabinia::draw()
{
	myCamera& camera=battle->get_camera();
	camera.draw_texture(TextureAsset(U"opabinia_shot").resized(image_size_int).rotated(image_angle), pos);
	//camera.draw_texture(hit_boxs, Color(250,100,0,100));
}
