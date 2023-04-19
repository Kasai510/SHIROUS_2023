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
		Harisenbong,
		Seahorse,
		Annkou,
		Poseidon,
		size
	};

	int generation = 2;//世代数。レベルみたいなもの。
	double Max_HP = 1000;
	double Max_LP = 1000;
	double draw_HP = Max_HP;
	double draw_LP = Max_LP;

	Array<std::shared_ptr<Option>> options;
	int spawning = 0;//0:通常モード。1～14:モード変更中。15:産卵モード。
	int select_spawn = 0;//産卵選択中のオプション。
	int select_spawn_counter = 0;//産卵するオプションの選択アニメーション用。
	int baby_counter = 180;//世代交代後のアニメーション用。
	int spawning_counter = 0;//産卵アニメーション用。
	
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
	void generation_up();//世代交代(レベルアップみたいなもの)した際の強化


	virtual void draw();
	virtual void draw_back();
	virtual void draw_front();

	void draw_spawning();


	int get_opt_size() { return options.size(); }
	Option& get_opt(int i) { return *options[i]; }

	Texture get_fish_texture(int type);
	double get_Max_HP() { return Max_HP; }
	double get_Max_LP() { return Max_LP; }
	double get_draw_HP() { return draw_HP; }
	double get_draw_LP() { return draw_LP; }
	double get_LP() { return LP; }
	void add_LP(double lp) { LP = Min(LP + lp, Max_LP); }
	int get_gen() { return generation; }
};
