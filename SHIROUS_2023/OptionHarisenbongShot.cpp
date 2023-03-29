#include "stdafx.h"
#include "OptionHarisenbongShot.h"

#include"Battle.h"
#include"StageObject.h"
#include"myIEffectClash.h"
#include"Enemy.h"

OptionHarisenbongShot::OptionHarisenbongShot(Battle* battle, const std::shared_ptr<class Fish>& master, double shot_arg)
	:OptionShot(battle, master),shot_arg(shot_arg)
{

	width = 80.0;
	height = 15.0;
	init_shot_arg = shot_arg;
	shot_phase = 1;
	shot_timer = 0;
	master_pos = master->get_pos();
	pos = master->get_pos();
	
	damage = 5;

	hit_box_origins << RectF(Arg::center(0, 0), width,height).asPolygon();
}

void OptionHarisenbongShot::update()
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


	if (battle->get_camera().in_camera(pos) == false) { over = true; }



	update_attack();



}

void OptionHarisenbongShot::update_attack()
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


void OptionHarisenbongShot::set_crash()
{
	battle->get_effects() << std::make_unique<myIEffectClash>(battle, pos, Palette::Yellow);
	over = true;
}


void OptionHarisenbongShot::move()
{
	if (auto s_master = master.lock())
	{

		master_pos = s_master->get_pos();
	}


	if (shot_phase == 1)
	{

		//バッと広がる
		pos = master_pos + 360 * shot_timer * Vec2{ cos(init_shot_arg),sin(init_shot_arg) };

		if (shot_timer >= 0.5)
		{
			shot_phase = 2;

			shot_timer = 0;

			//targetの決定
			for (auto& enemy : battle->get_enemies())
			{
				if (battle->get_camera().in_camera(enemy->get_rect()) && (enemy->get_pos() - master_pos).length() <= 1500)
				{
					if (decide_target == false || (enemy->get_pos() - master_pos).length() <= (target_pos - master_pos).length())
					{
						decide_target = true;

						target_pos = enemy->get_pos() + 70 * RandomVec2();
					}
				}
			}

			if (decide_target)
			{

				target_shot_arg = atan2(target_pos.y - pos.y, target_pos.x - pos.x);

			}
		}

	}
	else if (shot_phase == 2)
	{
		if (decide_target)
		{
			//shot_argを変える
			shot_arg += (target_shot_arg - shot_arg) / 8;
			//shot_arg += 20_deg;

			if (shot_timer >= 1)
			{
				shot_arg = target_shot_arg;
				shot_phase = 3;
			}

			pos = master_pos + 360 * 0.5 * Vec2{ cos(init_shot_arg),sin(init_shot_arg) };

		}
		else
		{
			shot_phase = 3;
		}
	}
	else if (shot_phase == 3)
	{
		pos += 3000 * Vec2{ cos(shot_arg),sin(shot_arg) }*battle->get_scene_del();
	}


	

	hit_boxs = hit_box_origins.rotated(shot_arg).movedBy(pos);
	
}

void OptionHarisenbongShot::draw()
{
	//get_hitbox().movedBy(-battle->get_camera().get_center()).movedBy(Scene::CenterF()).draw(Palette::Red);
	myCamera& camera = battle->get_camera();
	camera.draw_texture(TextureAsset(U"harisenbongshot").rotated(shot_arg),pos);

}
