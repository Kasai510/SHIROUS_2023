#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.3

class Menu
{
private:
	int scene_num = 0;
	int change_scene_to = -1;

	const Font fontBlack{ 100, Typeface::Black };
	const Font font50{ 50, Typeface::Black };

	bool instruction = false;
	int sellect = 0;
	int frame = 0;

	RectF start_game{ Arg::center(Scene::Center()), 400, 150 };
	RectF start_explain{ Arg::center(Scene::Center() + Vec2{0,200}), 300, 150 };

public:
	void update();
	void draw();

	bool change_scene_check();
	int change_scene();
};
