#include "Player.h"
#include"Battle.h"
#include"OptionShirous.h"
#include"OptionSeahorse.h"
#include"OptionPoseidon.h"
#include"OptionShirousShot.h"
#include"OptionCupinlaoyui.h"
#include"OptionHarisenbong.h"
#include"OptionAnnkou.h"

#include"myIEffectHeart.h"


Player::Player(Battle* battle):Fish(battle)
{

}


Player::Player(Battle* battle, Vec2 p):Fish(battle, p)
{
	set_name(U"シラス");
	set_image_name(U"shirous");
	Max_HP = 100 * generation;
	Max_LP = 100 * generation;
	hp = Max_HP;
	LP = Max_LP;
	draw_HP = hp;
	draw_LP = LP;
	for (int i = 0; i < 1;i++) {
		options << std::make_shared<OptionShirous>(battle, p);

	}

}
Player::~Player()
{

}

void Player::update()
{
	if (baby_counter < 180) baby_counter++;
	move();
	for (int i = 0; i < options.size(); i++)
	{
		options[i]->update(i);
	}

	spawn();

	options.remove_if([](const std::shared_ptr<Option>& option) {return option->is_dead(); });

	if (get_draw_HP() > get_HP())
	{
		if (get_draw_HP() > get_HP() + 3)draw_HP -= 3;
		else draw_HP = get_HP();
	}
	else if (get_draw_HP() < get_HP())
	{
		if (get_draw_HP() < get_HP() - 3)draw_HP += 3;
		else draw_HP = get_HP();
	}
	if (get_draw_LP() > get_LP())
	{
		if (get_draw_LP() > get_LP() + 3)draw_LP -= 3;
		else draw_LP = get_LP();
	}
	else if (get_draw_LP() < get_LP())
	{
		if (get_draw_LP() > get_LP() - 3)draw_LP += 3;
		else draw_LP = get_LP();
	}

}
void Player::move()
{
	input.update();

	double slowness = 10.0;
	if (spawning > 0)
	{
		speed.y += (0 - speed.y) / slowness;
		speed.x += (0 - speed.x) / slowness;
	}
	else
	{
		if (input.get_myButton_Up() > 0 && input.get_myButton_Down() > 0)speed.y += (0 - speed.y) / slowness;
		else if (input.get_myButton_Up() > 0)speed.y += (-1 - speed.y) / slowness;
		else if (input.get_myButton_Down() > 0)speed.y += (1 - speed.y) / slowness;
		else speed.y += (0 - speed.y) / slowness;

		if (input.get_myButton_Left() > 0 && input.get_myButton_Right() > 0)speed.x += (0 - speed.x) / slowness;
		else if (input.get_myButton_Left() > 0)speed.x += (-1 - speed.x) / slowness;
		else if (input.get_myButton_Right() > 0)speed.x += (1 - speed.x) / slowness;
		else speed.x += (0 - speed.x) / slowness;
	}
	
	

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

	//if (options[index]->ready_shot() && input.get_myButton_A() > 0) return true;
	return false;
}
std::shared_ptr<Shot> Player::opt_shot(int index)
{
	return options[index]->shot();
}

void Player::spawn()
{
	if (spawning == 0 && input.get_myButton_L() == 1)
	{
		spawning = 1;//産卵モード
		return;
	}
	if (spawning > 0 && spawning < 15)spawning++;
	

	//産卵モード
	if (spawning == 15)
	{
		if (select_spawn_counter == 0)
		{
			if (input.get_myButton_B() == 1)//Xキーで終了。
			{
				spawning = 0;//産卵モードを終了する。
				return;
			}


			if (input.get_myButton_Left() > 0 && input.get_myButton_Right() > 0) {}
			else if (input.get_myButton_Left() == 1) select_spawn_counter = -1;
			else if (input.get_myButton_Right() == 1) select_spawn_counter = +1;


			if (input.get_myButton_A() == 1 && get_LP() >= 0.9 * get_Max_LP())
			{
				//Zキーで世代交代。
				LP -= 0.9 * get_Max_LP();
				generation_up();
				for (int i = 0; i < 5; i++)
					battle->get_effects() << std::make_unique<myIEffectHeart>(battle, pos + RandomVec2() * Random() * 30, RandomVec2() * (1.0 + Random()) * 5, 15);
				baby_counter = 0;
				spawning = 0;
			}
			if (input.get_myButton_L() == 1)
			{
				//産卵。
				if (select_spawn == (int)FishType::Shirous && LP >= 100)
				{
					options << std::make_shared<OptionShirous>(battle, get_pos());
					LP -= 100;
					for (int i = 0; i < 5; i++)
						battle->get_effects() << std::make_unique<myIEffectHeart>(battle, pos + RandomVec2() * Random() * 30, RandomVec2() * (1.0 + Random()) * 5, 15);
				}
				if (select_spawn == (int)FishType::Harisenbong && LP >= 200)
				{
					options << std::make_shared<OptionHarisenbong>(battle, get_pos());
					LP -= 200;
					for (int i = 0; i < 5; i++)
						battle->get_effects() << std::make_unique<myIEffectHeart>(battle, pos + RandomVec2() * Random() * 30, RandomVec2() * (1.0 + Random()) * 5, 15);
				}
				if (select_spawn == (int)FishType::Seahorse && LP >= 250)
				{
					options << std::make_shared<OptionSeahorse>(battle, get_pos());
					LP -= 200;
					for (int i = 0; i < 5; i++)
						battle->get_effects() << std::make_unique<myIEffectHeart>(battle, pos + RandomVec2() * Random() * 30, RandomVec2() * (1.0 + Random()) * 5, 15);
				}
				if (select_spawn == (int)FishType::Annkou && LP >= 200)
				{
					options << std::make_shared<OptionAnnkou>(battle, get_pos());
					LP -= 200;
					for (int i = 0; i < 5; i++)
						battle->get_effects() << std::make_unique<myIEffectHeart>(battle, pos + RandomVec2() * Random() * 30, RandomVec2() * (1.0 + Random()) * 5, 15);
				}
				if (select_spawn == (int)FishType::Poseidon && LP >= 500)
				{
					options << std::make_shared<OptionPoseidon>(battle, get_pos());
					LP -= 300;
					for (int i = 0; i < 5; i++)
						battle->get_effects() << std::make_unique<myIEffectHeart>(battle, pos + RandomVec2() * Random() * 30, RandomVec2() * (1.0 + Random()) * 5, 15);
				}


				spawning = 0;
			}
		}
		

		if (select_spawn_counter > 0) select_spawn_counter++;
		if (select_spawn_counter < 0) select_spawn_counter--;
		if (select_spawn_counter == 6)
		{
			select_spawn++;
			while (select_spawn == (int)FishType::size) select_spawn = 0;
			select_spawn_counter = 0;
		}
		if (select_spawn_counter == -6)
		{
			select_spawn--;
			while (select_spawn == -1) select_spawn = (int)FishType::size -1;
			select_spawn_counter = 0;
		}	

		
	}
}

void Player::generation_up()
{
	generation = Min(generation + 1, 10);
	Max_HP = 100 * generation;
	hp = Max_HP;
	Max_LP = 100 * generation;
}

void Player::draw()
{
	myCamera& camera = battle->get_camera();
	// 自機の描画
	//TextureAsset(image_name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
	if (baby_counter < 180)
	{
		battle->get_camera().draw_texture(TextureAsset(U"shirous_dead"), get_pos().movedBy(0, -baby_counter), ColorF(1.0, 1.0, 1.0, 1.0 - baby_counter / 180.0));

		if (baby_counter < 90)battle->get_camera().draw_texture(TextureAsset(U"egg"), get_pos());
		else battle->get_camera().draw_texture(TextureAsset(image_name).scaled(baby_counter / 180.0), get_pos());
	}
	else battle->get_camera().draw_texture(TextureAsset(image_name), get_pos());
	
	
	//オプションの描画
	for (int i = 0; i < options.size(); i++)
	{
		options[i]->draw();
	}

	if (spawning > 0) draw_spawning();
}
void Player::draw_back()
{

}
void Player::draw_front()
{

}

void Player::draw_spawning()
{
	battle->get_camera().draw_texture(Circle(get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + 7.5 * spawning)), -150 * sin(ToRadians(30 + 7.5 * spawning))), 20), Palette::White);
	battle->get_camera().draw_texture(Circle(get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + 6 * spawning)), -150 * sin(ToRadians(30 + 6 * spawning))), 30), Palette::White);
	battle->get_camera().draw_texture(Circle(get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + 4 * spawning)), -150 * sin(ToRadians(30 + 4 * spawning))), 50), Palette::White);
	battle->get_camera().draw_texture(Circle(get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + 2 * spawning)), -150 * sin(ToRadians(30 + 2 * spawning))), 30), Palette::White);
	battle->get_camera().draw_texture(Circle(get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + 0.5 * spawning)), -150 * sin(ToRadians(30 + 0.5 * spawning))), 20), Palette::White);


	for (int i = -1; i < (int)FishType::size + 1; i++)
	{
		if (select_spawn - 1 <= i && i <= select_spawn + 1)
		{
			if (select_spawn == i)battle->get_camera().draw_texture(get_fish_texture(i).resized(90), get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + 4 * spawning)), -150 * sin(ToRadians(30 + 4 * spawning))));
			else battle->get_camera().draw_texture(get_fish_texture(i).resized(50), get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + (4 + 2 * (select_spawn - i)) * spawning)), -150 * sin(ToRadians(30 + (4 + 2 * (select_spawn - i)) * spawning))));
		}
	}

	for (int i = -2; i < (int)FishType::size + 2; i++)
	{
		if(i == select_spawn % (int)FishType::size)
			battle->get_camera().draw_texture(get_fish_texture(i).resized(90), get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + 4 * spawning)), -150 * sin(ToRadians(30 + 4 * spawning))));
		else if(i == select_spawn % (int)FishType::size + 1 || i == select_spawn % (int)FishType::size - 1)
			battle->get_camera().draw_texture(get_fish_texture(i).resized(50), get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + (4 + 2 * (select_spawn - i)) * spawning)), -150 * sin(ToRadians(30 + (4 + 2 * (select_spawn - i)) * spawning))));
		else if (i == select_spawn % (int)FishType::size + 2 || i == select_spawn % (int)FishType::size - 2)
			battle->get_camera().draw_texture(get_fish_texture(i).resized(30), get_pos().movedBy(0, +50).movedBy(150 * cos(ToRadians(30 + (4 + 1.75 * (select_spawn - i)) * spawning)), -150 * sin(ToRadians(30 + (4 + 1.75 * (select_spawn - i)) * spawning))));

	}


	
}

Texture Player::get_fish_texture(int type)
{
	while (type < 0)type += (int)FishType::size;
	while (type >= (int)FishType::size)type -= (int)FishType::size;

	if (type == (int)FishType::Shirous)return TextureAsset(U"shirous_opt");
	if (type == (int)FishType::Harisenbong)return TextureAsset(U"harisenbong");
	if (type == (int)FishType::Seahorse)return TextureAsset(U"seahorse");
	if (type == (int)FishType::Annkou)return TextureAsset(U"annkou");
	if (type == (int)FishType::Poseidon)return TextureAsset(U"poseidon");

	return TextureAsset(U"shirous");
}




