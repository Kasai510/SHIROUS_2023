#include "OptionShirousShot.h"
#include"Battle.h"
#include"StageObject.h"
#include"myIEffectClash.h"
#include"Enemy.h"

OptionShirousShot::OptionShirousShot(Battle* battle,const std::shared_ptr<class Fish>& master)
	:OptionShot(battle, master)
{

	width = 60.0;
	height = 60.0;


	shot_timer = 0;
	pos = master->get_pos_right();

	damage = 1;

	hit_box_origins << Circle(0, 0, 30).asPolygon();

}

void OptionShirousShot::update()
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

void OptionShirousShot::update_attack()
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


void OptionShirousShot::set_crash()
{
	battle->get_effects() << std::make_unique<myIEffectClash>(battle, pos);
	over = true;
}


void OptionShirousShot::move()
{
	pos.x += 1500*battle->get_scene_del();
	
	hit_boxs = hit_box_origins.movedBy(pos);
}

void OptionShirousShot::draw()
{
	//get_hitbox().movedBy(-battle->get_camera().get_center()).movedBy(Scene::CenterF()).draw(Palette::Red);
	myCamera& camera = battle->get_camera();
	camera.draw_texture(get_hitboxs(), Palette::Red);
	
}


