#pragma once
#include "Option.h"


class OptionAnnkou :
    public Option
{
private:
	bool now_attack_motion{ false };//アタックモーションを行っているか
	double attack_span{0};
	double attack_motion_timer{ 0 };

public:
	OptionAnnkou(Battle* battle);
	OptionAnnkou(Battle* battle, Vec2 pos);
	~OptionAnnkou();

	void update(int index);
	void move(int index);
	void move_intersect_stage(Stage_object stage);//現状、Fishクラスと同じ。
	void check_limit_stage(myCamera camera);//現状、Fishクラスと同じ。

	bool ready_shot();

	void attack_motion_update();
	void attack_motion_draw();
	void attack();


	void draw();
	void draw_back();
	void draw_front();

};

