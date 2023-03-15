#pragma once
# include "myCamera.h"
# include "myInput.h"

#include"Fish.h"
#include"Option.h"
#include"Shot.h"
#include"StageObject.h"
class Battle;
class Player : public Fish
{

protected:
	enum class FishType
	{
		Shirous,
		Seahorse,
		Poseidon,
		size
	};

	double Max_LP = 1000;
	double LP = Max_LP / 2.0;

	Array<std::shared_ptr<Option>> options;
	int spawning = 0;//0:通常モード。1～14:モード変更中。15:産卵モード。
	int select_spawn = 0;
	int select_spawn_counter = 0;//アニメーション用。
	
public:

	Player(Battle* battle);
	Player(Battle* battle, Vec2 pos);
	~Player();

	virtual void update();
	virtual void move();
	virtual void move_intersect_stage(Stage_object stage);
	virtual void check_limit_stage(myCamera camera);

	virtual bool ready_shot();
	virtual std::shared_ptr<Shot> shot();
	virtual bool ready_opt_shot(int index);
	virtual std::shared_ptr<Shot> opt_shot(int index);

	void spawn();


	virtual void draw();
	virtual void draw_back();
	virtual void draw_front();

	void draw_spawning();


	int get_opt_size() { return options.size(); }
	Option& get_opt(int i) { return *options[i]; }

	Texture get_fish_texture(int type);
	double get_Max_LP() { return Max_LP; }
	double get_LP() { return LP; }
};
