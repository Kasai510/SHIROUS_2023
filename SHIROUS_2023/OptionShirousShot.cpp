#include "OptionShirousShot.h"
#include"Battle.h"
#include"StageObject.h"
#include"EnemyColony.h"
#include"Enemy.h"

OptionShirousShot::OptionShirousShot(Battle* battle, Fish* master)
	:OptionShot(battle, master)
{

	width = 60.0;
	height = 60.0;


	shot_timer = 0;


}

void OptionShirousShot::update()
{
	shot_timer += battle->get_scene_del();


	if (crash == false)
	{
		if (shot_timer <= 0.5)
		{

			for (int i = 0; i < 6; i++)
			{
				poss[i] = master->get_pos_right() + Vec2{ 50,0 } + (60 - 120 * shot_timer) * Vec2 { cos(60_deg * i + 720_deg * shot_timer), sin(60_deg * i + 180_deg * shot_timer) };
			}
		}
		else
		{
			if (set_init_pos == false)
			{
				pos = master->get_pos_right() + Vec2{ 50,0 };
				set_init_pos = true;
			}
			move();
		}

		//壁との当たり判定
		if (shot_timer >= 0.6)
		{
			for (auto& stage_object : battle->get_stages())
			{
				if (get_hitcircle().intersects(stage_object.get_rect()))
				{
					crash = true;
					shot_timer = 0;
				}
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
	if (shot_timer >= 0.6)
	{
		for (auto& enemycolony : battle->get_enemy_colonys())
		{
			for (auto& enemy : enemycolony->get_enemys())
			{
				
				if (get_hitcircle().intersects(enemy->get_rect()))
				{
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
	if (shot_timer >= 0.6)
	{
		pos.x += 2000*battle->get_scene_del();
	
	}
}

void OptionShirousShot::draw()
{
	if (crash == false)
	{
		if (shot_timer <= 0.6)
		{
			for (auto& c_pos : poss)
			{

				Circle(Scene::CenterF() + (c_pos - battle->get_camera().get_center()) * battle->get_camera().get_scale(), 20).draw(Palette::White);
				Circle(Scene::CenterF() + (c_pos - battle->get_camera().get_center()) * battle->get_camera().get_scale(), 15).draw(Palette::Yellow);
			}

		}
		else {

			get_hitcircle().movedBy(-battle->get_camera().get_center()).movedBy(Scene::CenterF()).draw(Palette::Yellow);

		}
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

	Circle(Scene::CenterF() + (pos - battle->get_camera().get_center()) * battle->get_camera().get_scale(), (e * 100)).drawFrame((30.0 * (1.0 - e)), HSV(60, 1, 1, 0.7));
}

