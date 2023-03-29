#pragma once
#include "Fish.h"
class Enemy :
	public Fish//,public std::enable_shared_from_this<Enemy>
{
public:
	Enemy(Battle* battle,const Vec2& p);
	void update();
	void draw();
	virtual void move_intersect_stage(Stage_object stage) ;
	void move();
	void drop_item();
	void drop_LP();
protected:
	int time = 0;
	bool active = false;//画面内に入るまで動かない。
};

