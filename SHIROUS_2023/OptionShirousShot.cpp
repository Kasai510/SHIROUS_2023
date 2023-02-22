#include "OptionShirousShot.h"
#include"Battle.h"
#include"StageObject.h"
#include"EnemyColony.h"
#include"Enemy.h"

OptionShirousShot::OptionShirousShot(Battle* battle,const std::shared_ptr<class Fish>& master)
	:OptionShot(battle, master)
{

	width = 60.0;
	height = 60.0;


	shot_timer = 0;
	pos = master->get_pos_right();

	damage = 1;

	double dis;
	int target_index;	

}

void OptionShirousShot::update()
{
	shot_timer += battle->get_scene_del();


	if (crash == false)
	{

		move();

		//壁との当たり判定
		for (auto& stage_object : battle->get_stages())
		{
			if (get_hitcircle().intersects(stage_object.get_rect()))
			{
				crash = true;
				shot_timer = 0;
			}
		}
		

		if (pos.x >= battle->get_camera().get_center().x + 1000) { over = true; }

		update_attack();
	}
	else
	{
		update_crash();
	}

}

void OptionShirousShot::update_attack()
{
	//敵との当たり判定
	for (auto& enemycolony : battle->get_enemy_colonys())
	{
		for (auto& enemy : enemycolony->get_enemys())
		{
				
			if (get_hitcircle().intersects(enemy->get_rect()))
			{
				enemy->damage(damage);
				set_crash();
			}
				

			/*
			for (auto& record : records)
			{
				if (record.fish != enemy)
				{
					if (get_hitcircle().intersects(enemy->get_rect()))
					{
						records << Record(enemy, damage_span);
					}
				}
			}*/
		}
	}
	
}


void OptionShirousShot::set_crash()
{
	crash = true;
	shot_timer = 0;
}

void OptionShirousShot::update_crash()
{

	//発生から0.5秒たったら消す
	if (shot_timer > 0.5)
	{
		over = true;
	}
}

void OptionShirousShot::move()
{
		pos.x += 1500*battle->get_scene_del();
}

void OptionShirousShot::draw()
{
	if (crash == false)
	{

		get_hitcircle().movedBy(-battle->get_camera().get_center()).movedBy(Scene::CenterF()).draw(Palette::Red);

		
	}
	else
	{
		draw_crash();
	}
}


void OptionShirousShot::draw_crash()
{
	// イージング
	double e = EaseOutExpo(shot_timer);

	Circle(Scene::CenterF() + (pos - battle->get_camera().get_center()) * battle->get_camera().get_scale(), (e * 100)).drawFrame((30.0 * (1.0 - e)), HSV(1, 1, 1, 0.7));
}

