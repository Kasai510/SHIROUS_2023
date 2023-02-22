#include"OptionSeahorseShot.h"
#include"Battle.h"
#include"StageObject.h"
#include"EnemyColony.h"
#include"Enemy.h"

OptionSeahorseShot::OptionSeahorseShot(Battle* battle, const std::shared_ptr<class Fish>& master)
	:OptionShot(battle, master)
{

	width = 60.0;
	height = 60.0;


	shot_timer = 0;

	damage = 3;

}

void OptionSeahorseShot::update()
{
	shot_timer += battle->get_scene_del();


	if (crash == false)
	{

		if (master.lock())
		{
			std::shared_ptr shared_ptr_master = master.lock();


			if (shot_timer <= 0.5)
			{

				for (int i = 0; i < 6; i++)
				{
					poss[i] = shared_ptr_master->get_pos_right() + Vec2{ 50,0 } + (60 - 120 * shot_timer) * Vec2 { cos(60_deg * i + 720_deg * shot_timer), sin(60_deg * i + 180_deg * shot_timer) };
				}
			}
			else
			{
				if (set_init_pos == false)
				{
					pos = shared_ptr_master->get_pos_right() + Vec2{ 50,0 };
					set_init_pos = true;
				}
				move();
			}
		}
		else
		{
			set_crash();
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

void OptionSeahorseShot::update_attack()
{
	if (shot_timer >= 0.5)
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
			}
		}
	}
	
}


void OptionSeahorseShot::set_crash()
{
	crash = true;
	shot_timer = 0;
}

void OptionSeahorseShot::update_crash()
{

	//発生から0.5秒たったら消す
	if (shot_timer > 0.5)
	{
		over = true;
	}
}

void OptionSeahorseShot::move()
{
	if (shot_timer >= 0.6)
	{
		pos.x += 2500 * battle->get_scene_del();

	}
}

void OptionSeahorseShot::draw()
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


void OptionSeahorseShot::draw_crash()
{
	// イージング
	double e = EaseOutExpo(shot_timer);

	Circle(Scene::CenterF() + (pos - battle->get_camera().get_center()) * battle->get_camera().get_scale(), (e * 100)).drawFrame((30.0 * (1.0 - e)), HSV(60, 1, 1, 0.7));
}
