#pragma once
#include "OptionShot.h"
class OptionCupinlaoyuiShot :
    public OptionShot
{
protected:
	double shot_timer;
	Vec2 poss[6];
	bool set_init_pos{ false };

	std::weak_ptr<Fish> target;

public:
	//OptionShirousShot() {};
	OptionCupinlaoyuiShot(Battle*, const std::shared_ptr<class Fish>&);
	~OptionCupinlaoyuiShot() {};

	void set_crash();
	void update();
	void update_attack();

	void move();
	void draw();
};

