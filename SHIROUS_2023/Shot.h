#pragma once
# include "myCamera.h"

struct Record
{
	int id;
	double damage_span;
};

class Shot
{
protected:

	Vec2 pos{ 0,0 };
	double width = 20.0;
	double height = 20.0;


	double damage_span{0.5};



	Array<Record> records;//x:Fishのid y:damage_span

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
