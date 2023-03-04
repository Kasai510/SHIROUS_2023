#include "Fish.h"
#include"Battle.h"
int Fish::count_id;


Fish::Fish(Battle* battle):BattleObject(battle)
{
	ID = count_id;
	count_id++;
	draw_order = 5;
}
Fish::Fish(Battle* battle,const Vec2& p) :BattleObject(battle)
{
	ID = count_id;
	count_id++;
	pos = p;
	prev_pos = p;
	draw_order = 5;
}
Fish::~Fish()
{

}

void Fish::update()
{
	move();

}
void Fish::move()
{
	input.update();

	double slowness = 10.0;
	if (input.get_myButton_Up() > 0 && input.get_myButton_Down() > 0)speed.y += (0 - speed.y) / slowness;
	else if (input.get_myButton_Up() > 0)speed.y += (-1 - speed.y) / slowness;
	else if (input.get_myButton_Down() > 0)speed.y += (1 - speed.y) / slowness;
	else speed.y += (0 - speed.y) / slowness;

	if (input.get_myButton_Left() > 0 && input.get_myButton_Right() > 0)speed.x += (0 - speed.x) / slowness;
	else if (input.get_myButton_Left() > 0)speed.x += (-1 - speed.x) / slowness;
	else if (input.get_myButton_Right() > 0)speed.x += (1 - speed.x) / slowness;
	else speed.x += (0 - speed.x) / slowness;

	prev_pos = pos;
	if (speed.length() > 1.0)pos += max_speed * speed.normalized();
	else pos += max_speed * speed;
}
void Fish::move_intersect_stage(Stage_object stage)
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
void Fish::check_limit_stage(myCamera camera)
{
	if (camera.get_limit_stage_min().y > get_pos_top().y)set_pos_top(camera.get_limit_stage_min().y);
	if (camera.get_limit_stage_max().y < get_pos_bottom().y)set_pos_bottom(camera.get_limit_stage_max().y);
	if (camera.get_limit_stage_min().x > get_pos_left().x)set_pos_left(camera.get_limit_stage_min().x);
	if (camera.get_limit_stage_max().x < get_pos_right().x)set_pos_right(camera.get_limit_stage_max().x);
}

bool Fish::ready_shot()
{
	if (shot_timer > 0)shot_timer--;
	if (shot_timer == 0 && input.get_myButton_A() > 0) return true;
	return false;
}
std::shared_ptr<Shot> Fish::shot()
{
	shot_timer = shot_cool_time;
	return std::make_shared<Shot>(battle,get_pos_right() );
}





void Fish::draw()
{
	myCamera& camera = battle->get_camera();
	// 自機の描画
	TextureAsset(image_name).resized(image_size_int).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
}
void Fish::draw_back()
{

}
void Fish::draw_front()
{

}

void Fish::damage(double d)
{
	hp -= d;
}


