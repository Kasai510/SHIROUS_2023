#include "stdafx.h"
#include "Background.h"
#include"Battle.h"

Background::Background(Battle* battle)
{
	this->battle = battle;
	Array<Vec2> arrayv;
	for (int i : step(-2,40)) {
		arrayv << Vec2{ i * 500+Random(-100,100,rng1),Random(750,800,rng1)};
	}
	arrayv= Spline2D{ arrayv }.asLineString(8);
	arrayv << Vec2{ 40 * 500, 1000 } << Vec2{-2 * 500, 1000};
	ground1 = Polygon(arrayv);
}

void Background::draw()
{
	myCamera& camera = battle->get_camera();

	{
		Mat3x2 mat = Mat3x2::Translate(-camera.get_center() * 1).scaled(camera.get_scale(), { 0,0 }).translated(Scene::Center());
		Transformer2D tf{ mat };
		ground1.draw(Color(175, 120, 72));

		TextureAsset(U"rock_1").resized(300).drawAt(0, 800);
		TextureAsset(U"kaimen_1").resized(400).drawAt(200, 760);
		TextureAsset(U"rock_1").resized(300).drawAt(1000, 750);
		TextureAsset(U"kaimen_1").resized(300).drawAt(1200,750);
		
	}
	{
		Mat3x2 mat = Mat3x2::Translate(-camera.get_center() * 0.9).scaled(camera.get_scale(), { 0,0 }).translated(Scene::Center());
		Transformer2D tf{ mat };

		//TextureAsset(U"rock_1").resized(300).drawAt(0, 800);
		//TextureAsset(U"rock_1").resized(300).drawAt(1000, 800);
	}
	
	sea_gradation.draw();

}

Image Background::make_sea_gradation()
{
	Image image(1920, 1080);
	for (auto p : step(image.size())) {

		double upline = -pow(p.x-1920/2,2) * 0.00025 + 700;
		double downline = 740;
		double minus = 0;
		if (upline > p.y) {
			minus = (upline - p.y)*0.5;
		}
		else if (p.y > downline) {
			minus = p.y-downline;
		}
		double d = Max(0.0, 200 - minus);
		image[p] = Color(0, 100, d, d);
	}
	return image;
}
