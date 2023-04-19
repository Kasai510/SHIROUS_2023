#include "stdafx.h"
#include "OptionAnnkouShot.h"
#include"Battle.h"
#include"StageObject.h"
#include"myIEffectClash.h"
#include"Enemy.h"

OptionAnnkouShot::OptionAnnkouShot(Battle* battle, const std::shared_ptr<class Fish>& master,double shot_arg)
	:OptionShot(battle, master)
{

	width = 30.0;
	height = 30.0;

	this->shot_arg = shot_arg;

	shot_timer = 0;
	pos = master->get_pos_top() + Vec2{ master->get_width()/2,0 };

	damage = 3;

	hit_box_origins << Circle(0, 0, width/2).asPolygon();

}

void OptionAnnkouShot::update()
{
	shot_timer += battle->get_scene_del();

	move();

	//壁との当たり判定
	for (auto& stage_object : battle->get_stages())
	{
		if (get_hitboxs().intersects(stage_object.get_rect()))
		{
			set_crash();
		}
	}


	if (pos.x >= battle->get_camera().get_center().x + 1000) { over = true; }

	update_attack();



}

void OptionAnnkouShot::update_attack()
{
	//敵との当たり判定

	for (auto& enemy : battle->get_enemies())
	{

		if (get_hitboxs().intersects(enemy->get_rect()))
		{
			enemy->damage(damage);
			set_crash();
		}



	}


}


void OptionAnnkouShot::set_crash()
{
	battle->get_effects() << std::make_unique<myIEffectClash>(battle, pos,Palette::Yellow);
	over = true;
}


void OptionAnnkouShot::move()
{
	pos += 1500 * Vec2{cos(shot_arg),sin(shot_arg)} *battle->get_scene_del();

	hit_boxs = hit_box_origins.movedBy(pos);
}

void OptionAnnkouShot::draw()
{
	//get_hitbox().movedBy(-battle->get_camera().get_center()).movedBy(Scene::CenterF()).draw(Palette::Red);
	myCamera& camera = battle->get_camera();
	camera.draw_texture(get_hitboxs(), Palette::Yellow);

}


