#pragma once
# include "myCamera.h"
# include "myInput.h"

#include"Option_fish.h"
#include"Player_shot.h"
#include"Stage_object.h"

class Fish
{


private:
	myInput input;

	String name = U"シラス";
	Array<opt_Fish> options;

	double width = 150.0;//自機の横幅(px)。
	double height = 30.0;//自機の縦幅(px)。

	Vec2 pos{ 400,400 };//中心の座標。
	Vec2 pre_pos{ 400,400 };//１フレーム前の中心の座標。

	double max_speed = 500.0 / 60.0;//最大移動速度(px/s)。
	Vec2 move_vec{ 0,0 };//移動方向ベクトル。x,yそれぞれ-1～+1。用いる時は単位化する。

	int shot_cool_time = 30;//ショットのクールタイム(フレーム)。
	int shot_timer = 0;//ショットのタイマー(フレーム)。



public:

	Fish();
	Fish(Vec2 pos);
	~Fish();

	void update();
	void move();

	void move_intersect_stage(Stage_object stage);
	void check_limit_stage(myCamera camera);

	bool ready_shot();
	Player_shot shot();
	bool ready_opt_shot(int index);
	Player_shot opt_shot(int index);
	


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

	int get_opt_size() { return options.size(); }
	opt_Fish get_opt(int i) { return options[i]; }


};
