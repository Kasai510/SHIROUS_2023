#include"OptionSeahorseShot.h"
#include"Battle.h"
#include"StageObject.h"
#include"myIEffectClash.h"
#include"Enemy.h"

OptionSeahorseShot::OptionSeahorseShot(Battle* battle, const std::shared_ptr<class Fish>& master)
	:OptionShot(battle, master)
{

	width = 60.0;
	height = 60.0;


	shot_timer = 0;

	damage = 25;

	hit_box_origins << Circle(0, 0, 30).asPolygon();

}

void OptionSeahorseShot::update()
{

	shot_timer += battle->get_scene_del();


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



	//壁との当たり判定
	if (shot_timer >= 0.6)
	{
		for (auto& stage_object : battle->get_stages())
		{
			if (get_hitboxs().intersects(stage_object.get_rect()))
			{
				crash = true;
				shot_timer = 0;
			}
		}
	}

	if (pos.x >= battle->get_camera().get_center().x + 1000) { over = true; }

	update_attack();


}

void OptionSeahorseShot::update_attack()
{
	if (shot_timer >= 0.5)
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
	
}


void OptionSeahorseShot::set_crash()
{
	battle->get_effects() << std::make_unique<myIEffectClash>(battle, pos);
	over = true;
}


void OptionSeahorseShot::move()
{
	if (shot_timer >= 0.6)
	{
		pos.x += 2500 * battle->get_scene_del();
		hit_boxs = hit_box_origins.movedBy(pos);

	}
}

void OptionSeahorseShot::draw()
{
	myCamera& camera = battle->get_camera();

	if (shot_timer <= 0.6)
	{
		for (auto& c_pos : poss)
		{
				
			camera.draw_texture(Circle{ c_pos,20 }, Palette::White);
			camera.draw_texture(Circle{ c_pos,15 }, Palette::Yellow);
		}

	}
	else {
		camera.draw_texture(get_hitboxs(), Palette::Yellow);
		

	}

}
