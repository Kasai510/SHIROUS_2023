#pragma once
#include "OptionShot.h"


class OptionSeahorseShot : public OptionShot
{
protected:
	double shot_timer;
	Vec2 poss[6];
	bool set_init_pos{ false };

public:
	//OptionSeahorseShot() {};
	OptionSeahorseShot(Battle*, const std::shared_ptr<class Fish>&);
	~OptionSeahorseShot() {};

	void set_crash();
	void update();
	void update_attack();

	void move();
	void draw();
};
