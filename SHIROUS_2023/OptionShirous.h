#pragma once
#include "Option.h"


class Battle;


class OptionShirous
	: public Option
{
public:
	OptionShirous(Battle* battle);
	OptionShirous(Battle* battle, Vec2 pos);
	~OptionShirous();

	void update(int index);
	void move(int index);
	void move_intersect_stage(Stage_object stage);//現状、Fishクラスと同じ。
	void check_limit_stage(myCamera camera);//現状、Fishクラスと同じ。

	bool ready_shot();


	void attack();


	void draw();
	void draw_back();
	void draw_front();

	Font font{ 30 };
};

