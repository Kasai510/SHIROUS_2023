#include "stdafx.h"
#include "OptionCupinlaoyui.h"
#include"OptionCupinlaoyuiShot.h"
#include"Battle.h"
#include"Fish.h"

class Fish;


OptionCupinlaoyui::OptionCupinlaoyui(Battle* battle)
	: Option(battle)
{
	set_name(U"キューピンラオユイ");
	set_image_name(U"cupinlaoyui");
}
OptionCupinlaoyui::OptionCupinlaoyui(Battle* battle, Vec2 p)
	: Option(battle, p)
{
	set_name(U"キューピンラオユイ");
	set_image_name(U"cupinlaoyui");
	option_pos_timer = Random(0, 600);

	shot_cool_time = 120;
	shot_timer = shot_cool_time;
}


OptionCupinlaoyui::~OptionCupinlaoyui()
{

}
void OptionCupinlaoyui::update(int index)
{
	move(index);
	attack();
}

void OptionCupinlaoyui::move(int index)
{


	double slowness = 100.0;

	int i = 1;
	int j = 1;
	while (j < index + 2)
	{
		i++;
		j += i;
	}
	j = i - (j - (index + 2));

	option_pos_timer++;
	if (option_pos_timer > 2 * Math::Pi * 60 * 2 * i * j)option_pos_timer -= 2 * Math::Pi * 60 * 2 * i * j;

	double dx = -100 * (i - 1) + 10 * sin(option_pos_timer / 60.0 / (2 * i));
	double dy = 100 * (j - 0.5 * (i + 1)) + 20 * sin(option_pos_timer / 60.0 / (2 * j));

	place = battle->get_player().get_pos().movedBy(dx, dy);
	speed += (place - get_pos()) / slowness;
	if (speed.length() > max_speed) speed = speed.normalized() * max_speed;

	prev_pos = pos;
	pos += speed;

	speed /= 1.1;



}
void OptionCupinlaoyui::move_intersect_stage(Stage_object stage)
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

	if (get_rect().intersects(stage.get_near_rect()))
	{
		Vec2 v = get_pos() - stage.get_pos();
		double k = (place - get_pos()).length() / 150.0;//÷150がOptionShirousに合わせたものだから、調整が要るかも。

		speed += v.normalized() * k;

	}
}
void  OptionCupinlaoyui::check_limit_stage(myCamera camera)
{
	if (camera.get_limit_stage_min().y > get_pos_top().y)set_pos_top(camera.get_limit_stage_min().y);
	if (camera.get_limit_stage_max().y < get_pos_bottom().y)set_pos_bottom(camera.get_limit_stage_max().y);
	if (camera.get_limit_stage_min().x > get_pos_left().x)set_pos_left(camera.get_limit_stage_min().x);
	if (camera.get_limit_stage_max().x < get_pos_right().x)set_pos_right(camera.get_limit_stage_max().x);
}


bool OptionCupinlaoyui::ready_shot()
{
	if (shot_timer > 0)shot_timer--;
	if (shot_timer == 0)
	{
		shot_timer = shot_cool_time;
		return true;
	}
	return false;
}

void OptionCupinlaoyui::attack()
{
	if (ready_shot())
	{
		battle->get_player_shots() << std::make_shared<OptionShirousShot>(battle, shared_from_this());
	}
}



void OptionCupinlaoyui::draw()
{
	myCamera& camera = battle->get_camera();
	// 自機の描画
	//TextureAsset(name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());

	//当たり判定の描画
	battle->get_camera().draw_texture(get_rect(), Palette::Red);

	TextureAsset(image_name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale(), Palette::Gray);
	font(shot_timer).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());




}
void OptionCupinlaoyui::draw_back()
{

}
void OptionCupinlaoyui::draw_front()
{

}
