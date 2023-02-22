#pragma once
#include "Shot.h"

class Battle;

class OptionShot : public Shot
{
protected:

public:
	OptionShot() {};
	OptionShot(Battle*,Vec2 p);
	OptionShot(Battle*, const std::shared_ptr<class Fish>&);
	~OptionShot() {};

	virtual void update();
	virtual void move();

	virtual void draw();
};

