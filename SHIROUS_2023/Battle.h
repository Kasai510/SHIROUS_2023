#pragma once
#include"myCamera.h"
# include"Player.h"
#include"StageObject.h"



//{ 1920,1080 }

class Battle
{
private:
	int scene_num = 2;
	int change_scene_to = -1;

	myCamera camera;

	Player player{ 0, {400,400} };
	Array<std::shared_ptr<Shot>> player_shots;

	Array<Stage_object> stages;

public:
	Battle();
	void update();
	void draw();

	bool change_scene_check();
	int change_scene();
};
