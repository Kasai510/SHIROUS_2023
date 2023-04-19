#pragma once
#include "stdafx.h"

class Menu
{
private:
	int scene_num = 0;
	int change_scene_to = -1;

	const Font font100{ 100, Typeface::Black };
	const Font font50{ 50, Typeface::Black };

	bool instruction = false;
	int sellect = 0;
	int frame = 0;


public:
	void update();
	void draw();

	bool change_scene_check();
	int change_scene();
};
