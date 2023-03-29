#pragma once
#include "OptionShot.h"
class OptionAnnkouShot :
    public OptionShot
{
	double shot_timer;
	double shot_arg;
	bool set_init_pos{ false };

	std::weak_ptr<Fish> target;



public:

	OptionAnnkouShot(Battle*, const std::shared_ptr<class Fish>&,double shot_arg);
	~OptionAnnkouShot() {};

	void set_crash();
	void update();
	void update_attack();

	void move();
	void draw();
};

