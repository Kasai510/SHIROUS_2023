﻿#pragma once
# include <Siv3D.hpp>
# include "myCamera.h"
#include"Stage_object.h"
#include"Player_shot.h"

class Option
{


private:
	String name;
	double width = 150.0;//自機の横幅(px)。
	double height = 50.0;//自機の縦幅(px)。

	Vec2 pos{ 400,400 };//中心の座標。
	Vec2 pre_pos{ 400,400 };//１フレーム前の中心の座標。

	double max_speed = 500.0 / 60.0;//最大移動速度(px/s)。
	Vec2 speed{ 0,0 };

	int shot_cool_time = 45;//ショットのクールタイム(フレーム)。
	int shot_timer = 0;//ショットのタイマー(フレーム)。

	int option_pos_timer = 0;//群れっぽい上下の振れ幅に使う（フレーム）。

	bool is_dead = false;



public:

	Option();
	Option(String name, Vec2 pos);
	~Option();

	void update(Vec2 player, int index);
	void move(Vec2 player, int index);
	void move_intersect_stage(Stage_object stage);
	void check_limit_stage(myCamera camera);
	//改善用
	//void move_intersect_stage2(Stage_object stage);
	//void check_limit_stage2(myCamera camera);

	bool ready_shot();
	Player_shot shot();





	void draw(myCamera camera);
	void draw_back(myCamera camera);
	void draw_front(myCamera camera);





	double get_width() { return width; }
	double get_height() { return height; }

	Vec2 get_pos() { return pos; }
	Vec2 get_pos_top() { return get_pos().movedBy(0, -height / 2.0); }
	Vec2 get_pos_bottom() { return get_pos().movedBy(0, height / 2.0); }
	Vec2 get_pos_left() { return get_pos().movedBy(-width / 2.0, 0); }
	Vec2 get_pos_right() { return get_pos().movedBy(width / 2.0, 0); }
	Vec2 get_pre_pos() { return pre_pos; }
	Vec2 get_pre_pos_top() { return get_pre_pos().movedBy(0, -height / 2.0); }
	Vec2 get_pre_pos_bottom() { return get_pre_pos().movedBy(0, height / 2.0); }
	Vec2 get_pre_pos_left() { return get_pre_pos().movedBy(-width / 2.0, 0); }
	Vec2 get_pre_pos_right() { return get_pre_pos().movedBy(width / 2.0, 0); }

	void set_pos(Vec2 p) { pos = p; }
	void set_pos_top(Vec2 p) { pos = p.movedBy(0, height / 2.0); }
	void set_pos_bottom(Vec2 p) { pos = p.movedBy(0, -height / 2.0); }
	void set_pos_left(Vec2 p) { pos = p.movedBy(width / 2.0, 0); }
	void set_pos_right(Vec2 p) { pos = p.movedBy(-width / 2.0, 0); }
	void set_pos_top(double y) { pos.y = y + height / 2.0; }
	void set_pos_bottom(double y) { pos.y = y - height / 2.0; }
	void set_pos_left(double x) { pos.x = x + width / 2.0; }
	void set_pos_right(double x) { pos.x = x - width / 2.0; }

	RectF get_rect() { return RectF(Arg::center(get_pos()), width, height); }
	RectF get_pre_rect() { return RectF(Arg::center(get_pre_pos()), width, height); }
	Line get_move_line_top() { return Line(get_pre_pos_top(), get_pos_top()); }
	Line get_move_line_bottom() { return Line(get_pre_pos_bottom(), get_pos_bottom()); }
	Line get_move_line_left() { return Line(get_pre_pos_left(), get_pos_left()); }
	Line get_move_line_right() { return Line(get_pre_pos_right(), get_pos_right()); }



	String get_name() { return name; }
	bool get_is_dead() { return is_dead; }
};
