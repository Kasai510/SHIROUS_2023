#include "stdafx.h"
#include "OptionPoseidonShot2.h"
#include "OptionShirousShot.h"
#include"Battle.h"
#include"StageObject.h"
#include"Enemy.h"

OptionPoseidonShot2::OptionPoseidonShot2(Battle* battle, const std::shared_ptr<class Fish>& master)
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

void OptionPoseidonShot2::update()
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
		else if (phase == 1)
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

void OptionPoseidonShot2::update_attack()
{

	for (auto& record : records)
	{
		record.damage_span -= battle->get_scene_del();

	}

	records.remove_if([](const Record record) {return record.damage_span <= 0; });




	//敵との当たり判定
	
	for (auto& enemy : battle->get_enemies())
	{
		bool hit = false;//攻撃があたっているか
		if (hit_r.intersects(enemy->get_rect()) || hit_c.intersects(enemy->get_rect()))
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

				enemy->damage(damage - 8);
				enemy->set_speed(enemy->get_speed() + Vec2{ 100,0 });
				records << Record(enemy, damage_span);
			}

		}
	}
	

}


void OptionPoseidonShot2::set_crash()
{
	crash = true;
	shot_timer = 0;
}

void OptionPoseidonShot2::update_crash()
{

	//発生から0.5秒たったら消す
	if (shot_timer > 0.5)
	{
		over = true;
	}
}

void OptionPoseidonShot2::move()
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
			hit_r_h -= 100 * battle->get_scene_del();


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

void OptionPoseidonShot2::draw()
{


	battle->get_camera().draw_texture(hit_r, Palette::Yellow);

	battle->get_camera().draw_texture(hit_c, Palette::Yellow);

	RectF hit_r2 = RectF{ Arg::center(hit_r.center()),hit_r_l,hit_r_h - 60 <= 0 ? hit_r_h : hit_r_h - 60 };
	battle->get_camera().draw_texture(hit_r2, Palette::White);

	Circle hit_c2 = Circle{ hit_c.center,hit_c_r - 40 <= 0 ? hit_c_r : hit_c_r - 40 };
	battle->get_camera().draw_texture(hit_c2, Palette::White);



}


void OptionPoseidonShot2::draw_crash()
{
	// イージング
	double e = EaseOutExpo(shot_timer);

	Circle(Scene::CenterF() + (pos - battle->get_camera().get_center()) * battle->get_camera().get_scale(), (e * 100)).drawFrame((30.0 * (1.0 - e)), HSV(1, 1, 1, 0.7));
}
