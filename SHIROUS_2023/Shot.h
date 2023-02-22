#pragma once
# include "myCamera.h"

class Fish;
class Battle;


struct Record
{
	std::weak_ptr<Fish> fish;
	double damage_span;
};

class Shot
{
protected:

	Vec2 pos{ 0,0 };
	double width = 20.0;
	double height = 20.0;

	double damage = 1;

	double damage_span{ 0.5 };

	Battle* battle;
	std::weak_ptr<Fish> master;//発射した人

	Polygon hit_box;
	Polygon hit_box_origin;

	Array<Record> records;//x:Fishのポインタ y:damage_span

	bool crash = false;//着弾した時に破裂する
	bool over = false;

public:
	Shot() {};
	Shot(Battle*,Vec2 p);
	Shot(Battle*, const std::shared_ptr<class Fish>& );
	~Shot() {};

	virtual void update();
	virtual void move();

	virtual void draw();


	Vec2 get_pos() { return pos; }
	Polygon get_hitbox();
	bool get_over() { return over; }

};
