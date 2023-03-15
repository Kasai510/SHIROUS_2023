#include "Option.h"
#include"OptionShot.h"
#include"Battle.h"
#include"OptionShirousShot.h"



Option::Option(Battle* battle):Fish(battle)
{
	/*
	set_name(U"シラス");
	set_image_name(U"shirous");
	*/
}
Option::Option(Battle* battle, Vec2 p):Fish(battle, p)
{
	/*
	set_name(U"シラス");
	set_image_name(U"shirous");
	option_pos_timer = Random(0, 600);
	*/
}


Option::~Option()
{

}
void Option::update(Vec2 player, int index)
{
	move(player, index);
}
void Option::move(Vec2 player, int index)
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

	if (get_rect().intersects(stage.get_near_rect()))
	{
		Vec2 v = get_pos() - stage.get_pos();
		double k = (place - get_pos()).length() / 150.0;//÷150がOptionShirousに合わせたものだから、調整が要るかも。

		speed += v.normalized() * k;

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


void Option::draw()
{
	myCamera& camera = battle->get_camera();
	// 自機の描画
	//TextureAsset(name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
	TextureAsset(image_name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale(), Palette::Gray);
	font(ID).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
}
void Option::draw_back()
{

}
void Option::draw_front()
{

}
