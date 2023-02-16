﻿#pragma once
# include "Fish.h"
#include"OptionShot.h"


class Option : public Fish
{
protected:
	int option_pos_timer = 0;//群れっぽい上下の振れ幅に使う（フレーム）。


public:

	Option();
	Option(int id, Vec2 pos);
	~Option();

	virtual void update(Vec2 player, int index);
	virtual void move(Vec2 player, int index);
	virtual void move_intersect_stage(Stage_object stage);//現状、Fishクラスと同じ。
	virtual void check_limit_stage(myCamera camera);//現状、Fishクラスと同じ。

	virtual bool ready_shot();
	virtual std::shared_ptr<Shot> shot();


	virtual void draw(myCamera camera);
	virtual void draw_back(myCamera camera);
	virtual void draw_front(myCamera camera);
};