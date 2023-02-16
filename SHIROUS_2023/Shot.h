#pragma once
# include "myCamera.h"

class Fish;
class Battle;

struct Record
{
	std::shared_ptr<Fish> fish;
	double damage_span;
};

class Shot
{
protected:

	Vec2 pos{ 0,0 };
	double width = 20.0;
	double height = 20.0;


	double damage_span{ 0.5 };

	Battle* battle;
	Fish* master;//発射した人

	Array<Record> records;//x:Fishのポインタ y:damage_span

	bool over = false;

public:
	Shot() {};
	Shot(Battle*,Vec2 p);
	Shot(Battle*,Fish*);
	~Shot() {};

	virtual void update();
	virtual void move();

	virtual void draw();


	Vec2 get_pos() { return pos; }
	RectF get_hitbox();
	bool get_over() { return over; }

};
