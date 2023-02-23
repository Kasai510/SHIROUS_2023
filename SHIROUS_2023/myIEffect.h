#pragma once
class myIEffect
{
public:
	myIEffect(class Battle* b) {
		battle = b;
	}
	virtual void update() = 0;
	virtual void draw() = 0;
	bool isdead() {
		return dead;
	}
protected:
	Battle* battle;
	int time = 0;
	bool dead = false;
};

