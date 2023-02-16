#pragma once
# include "myCamera.h"

class Fish;

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



	Array<Record> records;//x:Fishのポインタ y:damage_span

	bool over = false;

public:
	Shot() {};
	Shot(Vec2 p);
	~Shot() {};

	virtual void update();
	virtual void move();

	virtual void draw(myCamera camera);


	Vec2 get_pos() { return pos; }
	RectF get_hitbox();
	bool get_over() { return over; }

};
