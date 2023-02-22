#pragma once
#include "EnemyShot.h"
class EnemyShotPikaia :
    public EnemyShot
{
public:
	EnemyShotPikaia(Battle* battle, const Vec2 p);
	double calc_angle();
	void update();

	void draw();
private:
	double angle;
	bool mode_stop;
	double image_size_int;
	Polygon hit_box_origin;
	Polygon hit_box;
	Stopwatch time;
};

