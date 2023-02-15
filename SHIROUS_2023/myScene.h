#pragma once

#include"Menu.h"
//#include"Character_sellect.h"
#include"Battle.h"

class myScene
{
private:
	int scene_num = 2;//現在動いているシーン
	//0:Manu
	//1:Character_sellect
	//2:Battle
	//

	int change_scene_to = 0;//遷移先のscene_num
	int change_scene_count = 0;//シーン遷移のカウンター。遷移開始時に60になり、1fpsで減っていく。
	double change_scene_fade = 0;//シーン遷移のフェードアウト

	//ゲーム中のそれぞれのシーン
	Menu menu;
	//Character_sellect character_sellect;
	Battle battle;


public:
	myScene();
	void update();
	void draw();

	void change_scene(int n);
	void change_scene_update();
	void change_scene_draw();
};
