#pragma once
#include"myCamera.h"


class Stage_object
{
protected:
	Vec2 pos;
	Vec2 pre_pos;
	double width;
	double height;

public:
	Stage_object(Vec2 p, double w, double h);
	Stage_object(const Rect& rect);
	void update();

	void draw(myCamera camera);



	double get_width() { return width; }
	double get_height() { return height; }

	Vec2 get_pos() { return pos; }
	double get_top() { return (get_pos().y - height / 2.0); }
	double get_bottom() { return (get_pos().y + height / 2.0); }
	double get_left() { return (get_pos().x - width / 2.0); }
	double get_right() { return (get_pos().x + width / 2.0); }
	Vec2 get_pre_pos() { return pre_pos; }
	double get_pre_top() { return (get_pre_pos().y - height / 2.0); }
	double get_pre_bottom() { return (get_pre_pos().y + height / 2.0); }
	double get_pre_left() { return (get_pre_pos().x - width / 2.0); }
	double get_pre_right() { return (get_pre_pos().x + width / 2.0); }
	RectF get_rect() { return RectF(Arg::center(get_pos()), width, height); }
};

