#pragma once
#include "Shot.h"
class OptionShot : public Shot
{
protected:
	

public:
	OptionShot() {};
	OptionShot(Vec2 p);
	~OptionShot() {};

	virtual void update();
	virtual void move();

	virtual void draw(myCamera camera);
};

