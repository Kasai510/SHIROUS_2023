#pragma once
#include "OptionShot.h"
class OptionHarisenbongShot :
    public OptionShot
{
protected:
	double shot_timer;


	Vec2 master_pos;

	int shot_phase{ 1 };


	double init_shot_arg{ 0 };
	double shot_arg{0};
	double target_shot_arg{0};

	bool set_init_pos{ false };
	bool decide_target{ false };
	
	Vec2 target_pos{0,0};

public:
	//OptionShirousShot() {};
	OptionHarisenbongShot(Battle*, const std::shared_ptr<class Fish>&,double shot_arg);
	~OptionHarisenbongShot() {};

	void set_crash();
	void update();
	void update_attack();

	void move();
	void draw();
};

