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
	int time=0;
};

