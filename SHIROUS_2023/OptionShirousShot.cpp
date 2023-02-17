#include "OptionShirousShot.h"
#include"Battle.h"

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



	if (shot_timer <= 1.5)
	{
		
		for (int i = 0; i < 6; i++)
		{
			poss[i] = master->get_pos_right() + Vec2{ 50,0 } + (60 - 35 * shot_timer) * Vec2 { cos(60_deg * i + 360_deg * shot_timer), sin(60_deg * i + 45_deg * shot_timer) };
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

}

void OptionShirousShot::attack()
{
	
}

void OptionShirousShot::move()
{
	if (shot_timer >= 1.5)
	{
		pos.x += 1600*battle->get_scene_del();
	
	}
}

void OptionShirousShot::draw()
{
	if (shot_timer <= 1.5)
	{
		for (auto& c_pos : poss)
		{

			Circle(Scene::CenterF() + (c_pos - battle->get_camera().get_center()) * battle->get_camera().get_scale(), 20).draw(Palette::White);
			Circle(Scene::CenterF() + (c_pos - battle->get_camera().get_center()) * battle->get_camera().get_scale(), 15).draw(Palette::Yellow);
		}

	}else{

		get_hitbox().movedBy(-battle->get_camera().get_center()).scaledAt({ 0,0 }, battle->get_camera().get_scale()).movedBy(Scene::CenterF()).draw(Palette::Yellow);

	}
}
