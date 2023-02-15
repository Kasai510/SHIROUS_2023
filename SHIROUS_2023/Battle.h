#pragma once
#include"myCamera.h"
# include"Player_fish.h"
#include"Stage_object.h"



//{ 1920,1080 }

class Battle
{
private:
	int scene_num = 2;
	int change_scene_to = -1;

	myCamera camera;

	Player player{ {400,400} };
	Array<Player_shot> player_shots;

	Array<Stage_object> stages;

public:
	Battle();
	void update();
	void draw();

	bool change_scene_check();
	int change_scene();
};
