#pragma once
#include "OptionShot.h"


class OptionShirousShot : public OptionShot
{
protected:
	double shot_timer;
	Vec2 poss[6];
	bool set_init_pos{ false };

	std::weak_ptr<Fish> target;

public:
	//OptionShirousShot() {};
	OptionShirousShot(Battle*, const std::shared_ptr<class Fish>&);
	~OptionShirousShot() {};

	void set_crash();
	void update();
	void update_attack();

	void move();
	void draw();
};

