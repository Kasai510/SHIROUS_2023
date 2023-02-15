#include "Player_fish.h"



Player::Player()
{

}
Player::Player(Vec2 p)
{
	pos = p;
	pre_pos = p;

	options << std::make_shared<Option>(U"イワシ", p);
	options << std::make_shared<Option>(U"イワシ", p);
	options << std::make_shared<Option>(U"イワシ", p);
	options << std::make_shared<Option>(U"イワシ", p);
	options << std::make_shared<Option>(U"イワシ", p);
	options << std::make_shared<Option>(U"イワシ", p);
	options << std::make_shared<Option>(U"イワシ", p);
	options << std::make_shared<Option>(U"イワシ", p);
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

	options.remove_if([](const std::shared_ptr<Option>& option) {return option->get_is_dead(); });

}
void Player::move()
{
	input.update();

	double slowness = 10.0;
	if (input.get_myButton_Up() > 0 && input.get_myButton_Down() > 0)move_vec.y += (0 - move_vec.y) / slowness;
	else if (input.get_myButton_Up() > 0)move_vec.y += (-1 - move_vec.y) / slowness;
	else if (input.get_myButton_Down() > 0)move_vec.y += (1 - move_vec.y) / slowness;
	else move_vec.y += (0 - move_vec.y) / slowness;

	if (input.get_myButton_Left() > 0 && input.get_myButton_Right() > 0)move_vec.x += (0 - move_vec.x) / slowness;
	else if (input.get_myButton_Left() > 0)move_vec.x += (-1 - move_vec.x) / slowness;
	else if (input.get_myButton_Right() > 0)move_vec.x += (1 - move_vec.x) / slowness;
	else move_vec.x += (0 - move_vec.x) / slowness;

	pre_pos = pos;
	if (move_vec.length() > 1.0)pos += max_speed * move_vec.normalized();
	else pos += max_speed * move_vec;


	

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
Player_shot Player::shot()
{
	shot_timer = shot_cool_time;
	return Player_shot{ U"シラス" ,get_pos_right()};
}
bool Player::ready_opt_shot(int index)
{
	if (options[index]->ready_shot() && input.get_myButton_A() > 0) return true;
	return false;
}
Player_shot Player::opt_shot(int index)
{
	return options[index]->shot();
}

void Player::draw(myCamera camera)
{
	// 自機の描画
	//get_rect().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).draw(Palette::White);
	TextureAsset(name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());

	//オプションの描画
	for (int i = 0; i < options.size(); i++)
	{
		options[i]->draw(camera);
	}

}
void Player::draw_back(myCamera camera)
{

}
void Player::draw_front(myCamera camera)
{

}





