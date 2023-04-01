#pragma once
#include "EnemyShot.h"
class EnemyShotOpabinia :
    public EnemyShot
{
public:
	EnemyShotOpabinia(class Battle* battle,const Vec2& p);
	void update();
	void draw();
private:
	int32 image_size_int;
	double image_angle;
};

