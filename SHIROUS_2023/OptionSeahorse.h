#pragma once
#include "Option.h"

class Battle;

class OptionSeahorse : public Option
{
public:
	OptionSeahorse(Battle* battle);
	OptionSeahorse(Battle* battle, Vec2 pos);
	~OptionSeahorse();

	void update(int index);
	void move(int index);
	void move_intersect_stage(Stage_object stage);//現状、Fishクラスと同じ。
	void check_limit_stage(myCamera camera);//現状、Fishクラスと同じ。

	bool ready_shot();
	std::shared_ptr<Shot> shot();


	void draw();
	void draw_back();
	void draw_front();

	Font font{ 30 };
};
