#include "Player.h"
#include"Battle.h"
#include"OptionShirousShot.h"


Player::Player(Battle* battle):Fish(battle)
{

}
Player::Player(Battle* battle, Vec2 p):Fish(battle, p)
{
	set_name(U"シラス");
	set_image_name(U"shirous");
	for (int i : step(2)) {
		options << std::make_shared<Option>(battle, p);
	}
}
Player::~Player()
{

}

void Player::update()
{
	move();

	for (int i = 0; i < options.size(); i++)
	{
		options[i]->move(get_pos(), i);
	}

	options.remove_if([](const std::shared_ptr<Option>& option) {return option->is_dead(); });

}
void Player::move()
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

void Player::move_intersect_stage(Stage_object stage)
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

	for (int i = 0; i < options.size(); i++)
	{
		options[i]->move_intersect_stage(stage);
	}

}
void  Player::check_limit_stage(myCamera camera)
{
	if (camera.get_limit_stage_min().y > get_pos_top().y)set_pos_top(camera.get_limit_stage_min().y);
	if (camera.get_limit_stage_max().y < get_pos_bottom().y)set_pos_bottom(camera.get_limit_stage_max().y);
	if (camera.get_limit_stage_min().x > get_pos_left().x)set_pos_left(camera.get_limit_stage_min().x);
	if (camera.get_limit_stage_max().x < get_pos_right().x)set_pos_right(camera.get_limit_stage_max().x);

	for (int i = 0; i < options.size(); i++)
	{
		options[i]->check_limit_stage(camera);
	}
}


bool Player::ready_shot()
{
	if (shot_timer > 0)shot_timer--;
	if (shot_timer == 0 && input.get_myButton_A() > 0) return true;
	return false;
}
std::shared_ptr<Shot> Player::shot()
{
	shot_timer = shot_cool_time;
	return std::make_shared<Shot>( battle,get_pos_right());

}
bool Player::ready_opt_shot(int index)
{
	if (options[index]->ready_shot() && input.get_myButton_A() > 0) return true;
	return false;
}
std::shared_ptr<Shot> Player::opt_shot(int index)
{
	return options[index]->shot();
}

void Player::draw()
{
	myCamera& camera = battle->get_camera();
	// 自機の描画
	TextureAsset(U"shirous").scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
	
	//オプションの描画
	for (int i = 0; i < options.size(); i++)
	{
		options[i]->draw();
	}

}
void Player::draw_back()
{

}
void Player::draw_front()
{

}





