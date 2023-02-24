#include "stdafx.h"
#include "OptionPoseidonShot.h"
#include "OptionShirousShot.h"
#include"Battle.h"
#include"StageObject.h"
#include"EnemyColony.h"
#include"Enemy.h"

OptionPoseidonShot::OptionPoseidonShot(Battle* battle, const std::shared_ptr<class Fish>& master)
	:OptionShot(battle, master)
{
	shot_timer = 0;
	pos = this->master.lock()->get_pos_right();

	damage = 10;
	damage_span = 1;
	end_shot_time = 4;

	hit_c = Circle(pos, 10);

	max_hit_c_r = 70;
	hit_c_r = 0;

	max_hit_r_l = 1920;
	hit_r_l = 0;

	max_hit_r_h = 70;
	hit_r_h = max_hit_r_h;
}

void OptionPoseidonShot::update()
{
	shot_timer += battle->get_scene_del();

	if (auto s_master = master.lock())
	{
		pos = s_master->get_pos_right() + Vec2{ max_hit_c_r,0 };
		//masterが生きている
		if (phase == 0)
		{
			//充電
			hit_c_r = 500 * shot_timer * shot_timer;
			if (hit_c_r >= max_hit_c_r)
			{
				shot_timer = 0;
				phase = 1;
			}
		}
		else if(phase == 1)
		{
			//溜め
			if (shot_timer >= 0.3)
			{
				phase = 2;
			}
			
		}
		else if (phase == 2)
		{
			//ビーム
			move();
		}

		//当たり判定の更新
		hit_c = Circle(pos, hit_c_r);
		hit_r = RectF(pos - Vec2{ 0,hit_r_h / 2 }, hit_r_l, hit_r_h);

		update_attack();
	}
	else
	{
		//masterが死んでいる
	}
		

}

void OptionPoseidonShot::update_attack()
{

	for (auto& record : records)
	{
		record.damage_span -= battle->get_scene_del();

	}

	records.remove_if([](const Record record) {return record.damage_span <= 0; });




	//敵との当たり判定
	for (auto& enemycolony : battle->get_enemy_colonys())
	{
		for (auto& enemy : enemycolony->get_enemys())
		{
			bool hit = false;//攻撃があたっているか
			if (hit_r.intersects(enemy->get_rect())|| hit_c.intersects(enemy->get_rect()))
			{
				hit = true;
			}

			//あたっているなら
			if (hit)
			{
				bool be_record = false;//すでにrecordの中に入っているか
				for (auto& record : records)
				{
					if (auto s_record_fish = record.fish.lock())
					{
						if (s_record_fish == enemy)
						{
							be_record = true;
							break;
						}
					}
				}


				if (be_record == false)
				{

					enemy->damage(damage);
					enemy->set_speed(enemy->get_speed() + Vec2{ 30,0 });
					records << Record(enemy, damage_span);

				}


			}
		}
	}

}


void OptionPoseidonShot::set_crash()
{
	crash = true;
	shot_timer = 0;
}


void OptionPoseidonShot::move()
{
	if (shot_timer <= end_shot_time)
	{
		//ビームが伸びる
		if (hit_r_l <= max_hit_r_l)
		{
			hit_r_l += 7000 * battle->get_scene_del();
		}
	}
	else
	{
		//ビームが消えていく
		if (hit_r_h >= 5)
		{
			hit_r_h -= 100* battle->get_scene_del();

			
			if (hit_c_r >= 2.5)
			{
				hit_c_r -= 50 * battle->get_scene_del();
				if (hit_c_r <= 0)
				{
					hit_c_r = 1.0;
				}
			}
		}
		else
		{
			over = true;
		}
	}


}

void OptionPoseidonShot::draw()
{

	Color framecolor = HSV(Random(0, 360), 1, 1);
	
	battle->get_camera().draw_texture(hit_r,framecolor);

	battle->get_camera().draw_texture(hit_c, framecolor);



	RectF hit_r2 = RectF{ Arg::center(hit_r.center()),hit_r_l,hit_r_h - 10 <= 0 ? hit_r_h : hit_r_h - 10 };
	battle->get_camera().draw_texture(hit_r2, HSV(66, 1, 1));

	Circle hit_c2 = Circle{ hit_c.center,hit_c_r - 5 <= 0 ? hit_c_r : hit_c_r - 5 };
	battle->get_camera().draw_texture(hit_c2, HSV(66, 1, 1));

	hit_r2 = RectF{ Arg::center(hit_r.center()),hit_r_l,hit_r_h - 30 <= 0 ? hit_r_h : hit_r_h - 30 };
	hit_c2.r = hit_c_r - 25 <= 0 ? hit_c_r : hit_c_r - 25;

	battle->get_camera().draw_texture(hit_r2, Palette::White);
	battle->get_camera().draw_texture(hit_c2, Palette::White);

}


