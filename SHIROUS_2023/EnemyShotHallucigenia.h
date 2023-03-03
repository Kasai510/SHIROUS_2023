#pragma once
#include "EnemyShot.h"
class EnemyShotHallucigenia :
    public EnemyShot
{
public:
	EnemyShotHallucigenia(Battle* battle, const Vec2& p);
	double calc_angle();
	void update();

	void draw();
private:
	double angle;
	double image_angle;
	bool mode_stop;
	double image_size_int;
};

