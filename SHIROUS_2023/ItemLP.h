#pragma once
#include "Item.h"
class ItemLP :
    public Item
{
protected:
	double LP;
	bool catched = false;
public:
	ItemLP(Battle* battle, const Vec2& p, double lp);

	void update();
	void move();


	void draw();
};

