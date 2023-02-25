#pragma once
class Background
{
public:
	Background(class Battle* battle);
	void draw();
	Image make_sea_gradation();
private:
	Battle* battle;
	Polygon ground1;
	SmallRNG rng1{ 123456789ull };
	Texture sea_gradation{ make_sea_gradation() };
	
};

