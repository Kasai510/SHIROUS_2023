#pragma once
# include "myCamera.h"

class Player_shot
{
private:
	String name;
	Vec2 pos{ 0,0 };
	double width = 20.0;
	double height = 20.0;

	bool over = false;

public:
	Player_shot() {};
	Player_shot(Vec2 p);
	Player_shot(String name, Vec2 p);
	~Player_shot() {};

	void update();
	void move();
	RectF get_hitbox();

	void draw(myCamera camera);


	Vec2 get_pos() { return pos; }
	bool get_over() { return over; }

};
