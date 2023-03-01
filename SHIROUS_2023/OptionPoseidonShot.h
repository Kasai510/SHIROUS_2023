#pragma once
#include "OptionShot.h"
class OptionPoseidonShot :
    public OptionShot
{
protected:
	double shot_timer;
	double end_shot_time;//shotの出ている時間
	Vec2 poss[6];
	bool set_init_pos{ false };

	int   phase = 0;//shotの段階

	std::weak_ptr<Fish> target;

	//当たり判定
	Circle hit_c;
	RectF hit_r;


	double max_hit_c_r{0};//hit_cの最大半径
	double hit_c_r{ 0 };//hit_cの半径


	double hit_r_l{ 0 };//hit_rの長さ
	double max_hit_r_l{ 0 };//hit_rの最大長さ
	double hit_r_h{ 0 };//hit_rの高さ
	double max_hit_r_h{ 0 };//hit_rの最大高さ

public:
	OptionPoseidonShot() {};
	OptionPoseidonShot(Battle*, const std::shared_ptr<class Fish>&);
	~OptionPoseidonShot() {};

	void set_crash();
	void update();
	void update_attack();

	void move();
	void draw();

};

