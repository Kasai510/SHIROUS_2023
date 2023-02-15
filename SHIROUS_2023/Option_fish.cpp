#include "Option_fish.h"

Option::Option()
{
	name = U"シラス";
}
Option::Option(String n, Vec2 p)
{
	name = n;
	pos = p;
	pre_pos = p;
	option_pos_timer = Random(0, 600);
}


Option::~Option()
{

}
void Option::update(Vec2 player, int index)
{
	move(player, index);

	if (shot_timer > 0)shot_timer--;

}
void Option::move(Vec2 player, int index)
{
	option_pos_timer++;
	if (option_pos_timer > 2 * Math::Pi * 60 * (index + 1))option_pos_timer -= 2 * Math::Pi * 60 * (index + 1);

	double slowness = 100.0;

	int i = 1;
	int j = 0;
	while (j < index)
	{
		i++;
		j += i;
	}

	Vec2 place = player.movedBy(-100 * i + 10 * sin(option_pos_timer / 60.0 / (index + 1)), 30 * i * sin(option_pos_timer / 60.0 / (index + 1)));
	speed += (place - get_pos()) / slowness;
	if (speed.length() > max_speed) speed = speed.normalized() * max_speed;

	pre_pos = pos;
	pos += speed;

	speed /= 1.1;

}
void Option::move_intersect_stage(Stage_object stage)
{
	if (get_rect().intersects(stage.get_rect()))
	{
		double dx = get_pos().x - stage.get_pos().x;

		if (stage.get_pre_pos().y + dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) < get_pre_pos().y
			&& stage.get_pre_pos().y - dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) < get_pre_pos().y)
		{
			set_pos_top(stage.get_bottom());
		}
		if (stage.get_pre_pos().y + dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) > get_pre_pos().y
			&& stage.get_pre_pos().y - dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) > get_pre_pos().y)
		{
			set_pos_bottom(stage.get_top());
		}
		if (stage.get_pre_pos().y + dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) > get_pre_pos().y
			&& stage.get_pre_pos().y - dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) < get_pre_pos().y)
		{
			set_pos_left(stage.get_right());
		}
		if (stage.get_pre_pos().y + dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) < get_pre_pos().y
			&& stage.get_pre_pos().y - dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) > get_pre_pos().y)
		{
			set_pos_right(stage.get_left());
		}

	}


}
void  Option::check_limit_stage(myCamera camera)
{
	if (camera.get_limit_stage_min().y > get_pos_top().y)set_pos_top(camera.get_limit_stage_min().y);
	if (camera.get_limit_stage_max().y < get_pos_bottom().y)set_pos_bottom(camera.get_limit_stage_max().y);
	if (camera.get_limit_stage_min().x > get_pos_left().x)set_pos_left(camera.get_limit_stage_min().x);
	if (camera.get_limit_stage_max().x < get_pos_right().x)set_pos_right(camera.get_limit_stage_max().x);
}


bool Option::ready_shot()
{
	if (shot_timer > 0)shot_timer--;
	if (shot_timer == 0) return true;
	return false;
}
Player_shot Option::shot()
{
	shot_timer = shot_cool_time;
	return Player_shot{ U"シラス" ,get_pos_right() };
}


void Option::draw(myCamera camera)
{
	// 自機の描画
	/*get_rect().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).draw(Palette::Black);
	get_rect().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).drawFrame(2, Palette::White);*/

	//TextureAsset(name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
	TextureAsset(U"シラス").scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale(), Palette::Gray);


	String texture_name = U"player_" + name;
	


}
void Option::draw_back(myCamera camera)
{

}
void Option::draw_front(myCamera camera)
{

}
