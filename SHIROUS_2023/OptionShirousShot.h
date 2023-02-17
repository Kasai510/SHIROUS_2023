#pragma once
#include "OptionShot.h"


class OptionShirousShot : public OptionShot
{
protected:
	double shot_timer;
	Vec2 poss[6];
	bool set_init_pos{ false };

public:
	OptionShirousShot() {};
	OptionShirousShot(Battle*,Fish*);
	~OptionShirousShot() {};

	void update();
	void attack();
	void move();
	void draw();
};

