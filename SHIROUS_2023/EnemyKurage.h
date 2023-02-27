﻿#pragma once
#include "Enemy.h"
class EnemyKurage :
    public Enemy
{
public:
	EnemyKurage(Battle* battle, Vec2 p);

	void update();
	void move();
	void draw();
private:
	int jump_wait_time = 0;
	int first_level;
	bool isGoRight = true;
	MultiPolygon hit_boxs;
};

