#pragma once
#include "Fish.h"
class Enemy :
    public Fish
{
public:
	Enemy(Battle* battle,Vec2 p);

	virtual void update()=0;
};

