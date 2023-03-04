#include "stdafx.h"
#include "Background.h"
#include"Battle.h"

Background::Background(Battle* battle):BattleObject(battle)
{

	//make_ground1();
	//make_ground2();
	//write_file_ground();
	read_file_ground();
	draw_order = 1;
	
}

void Background::draw()
{
	myCamera& camera = battle->get_camera();
	{
		Mat3x2 mat = Mat3x2::Translate((Scene::Center() - camera.get_center()) * 0.2).scaled(camera.get_scale(), Scene::Center());
		Transformer2D tf{ mat };
		ground2.draw(Color(165, 110, 72));
		TextureAsset(U"rock_1").resized(300).drawAt(0, 800);
		//TextureAsset(U"rock_1").resized(300).drawAt(1000, 800);
	}
	{
		Mat3x2 mat = Mat3x2::Translate(Scene::Center() - camera.get_center()).scaled(camera.get_scale(), Scene::Center());
		Transformer2D tf{ mat };
		ground1.draw(Color(185, 130, 82));

		TextureAsset(U"rock_1").resized(300).drawAt(0, 800);
		TextureAsset(U"kaimen_1").resized(400).drawAt(200, 760);
		TextureAsset(U"rock_1").resized(300).drawAt(1000, 750);
		TextureAsset(U"kaimen_1").resized(300).drawAt(1200,750);
		
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

void Background::make_ground1()
{
	
	Array<Vec2> arrayv;
	for (int i : step(-2, 50)) {
		arrayv << Vec2{ i * 500 + Random(-100,100,rng1),Random(750,800,rng1) };
	}
	arrayv = Spline2D{ arrayv }.asLineString(4);
	arrayv << Vec2{ 50 * 500, 1000 } << Vec2{ -2 * 500, 1000 };
	ground1 = Polygon(arrayv);
}

void Background::make_ground2()
{
	
	Array<Vec2> arrayv2;
	for (int i : step(-2, 60)) {
		arrayv2 << Vec2{ i * 100 + Random(-30,30,rng1),Random(670,700,rng1) };
	}
	arrayv2 = Spline2D{ arrayv2 }.asLineString(4);
	arrayv2 << Vec2{ 60 * 100, 1000 } << Vec2{ -2 * 100, 1000 };
	ground2 = Polygon(arrayv2);

}


void Background::write_file_ground()
{
	// 書き込み用のバイナリファイルをオープン
	Serializer<BinaryWriter> writer{ U"data/binary/background/ground_cumbria.bin" };
	if (not writer) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `data/binary/background/ground_cumbria.bin`" };
	}
	writer(ground1, ground2);
}

void Background::read_file_ground()
{
	Deserializer<BinaryReader> reader{ U"data/binary/background/ground_cumbria.bin" };

	if (not reader) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `data/binary/background/ground_cumbria.bin`" };
	}

	reader(ground1, ground2);
}
