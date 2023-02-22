#pragma once
# include "Fish.h"
#include"OptionShot.h"

class Battle;

class Option
	: public Fish//, public std::enable_shared_from_this<Option>
{
protected:
	int option_pos_timer = 0;//群れっぽい上下の振れ幅に使う（フレーム）。

	Array<std::shared_ptr<Shot>> optionshots;


public:

	Option(Battle* battle);
	Option(Battle* battle, Vec2 pos);
	~Option();

	virtual void update(Vec2 player, int index);
	virtual void update(int index) {};

	virtual void move(Vec2 player, int index);
	virtual void move_intersect_stage(Stage_object stage);//現状、Fishクラスと同じ。
	virtual void check_limit_stage(myCamera camera);//現状、Fishクラスと同じ。
	


	virtual bool ready_shot();




	virtual void draw();
	virtual void draw_back();
	virtual void draw_front();

	void damage() {};
	Font font{ 30 };
};
