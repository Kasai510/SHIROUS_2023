#pragma once
#include"BattleObject.h"
class Background:public BattleObject
{
public:
	Background(class Battle* battle);
	void draw();
	Image make_sea_gradation();
private:
	Polygon ground1;
	Polygon ground2;
	SmallRNG rng1{ 123456789ull };
	Texture sea_gradation{ make_sea_gradation() };

	void make_ground1();
	void make_ground2();
	void write_file_ground();
	void read_file_ground();
	
};

