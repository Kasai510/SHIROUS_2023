#pragma once
#include"BattleObject.h"
class myIEffect:public BattleObject
{
public:
	myIEffect(class Battle* b):BattleObject(b) {
		draw_order = 8;
	}
	virtual void update() = 0;
	virtual void draw() = 0;
	bool isdead() {
		return dead;
	}
protected:
	int time = 0;
	bool dead = false;
};

