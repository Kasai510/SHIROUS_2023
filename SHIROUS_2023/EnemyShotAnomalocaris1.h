#pragma once
#include "EnemyShot.h"

class Battle;

class EnemyShotAnomalocaris1 :
    public EnemyShot
{
private:
	//当たり判定
	Circle hit_c;

	double hit_r{ 5 };//半径
	double shot_arg{0};
	bool can_move{ false };//shotを動かすか
	double time = 0;

public:
	EnemyShotAnomalocaris1(Battle* battle, const Vec2& p,double shot_arg);
	
	void update();
	void move();
	void draw();

};

