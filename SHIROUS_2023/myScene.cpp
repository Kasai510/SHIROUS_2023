#include "myScene.h"

myScene::myScene()
{
	
}

void myScene::update()
{

	if (change_scene_count == 0)//シーン遷移中ではないなら
	{
		switch (scene_num)
		{
		case 0:
			menu.update();
			if (menu.change_scene_check())
			{
				change_scene(menu.change_scene());
			}
			break;
		case 2:
			battle.update();
			if (battle.change_scene_check())
			{
				change_scene(battle.change_scene());
			}
			break;
		default:
			break;
		}
	}
	else if (change_scene_count > 0) change_scene_update();
}

void myScene::draw()
{
	switch (scene_num)
	{
	case 0:
		menu.draw();
		break;
	case 2:
		battle.draw();
		break;
	default:
		break;

	}

	if (change_scene_count > 0) change_scene_draw();
}

void myScene::change_scene(int n)
{
	change_scene_to = n;
	change_scene_count = 60;
}
void myScene::change_scene_update()
{
	if (change_scene_count > 30)change_scene_fade += 0.03;
	if (change_scene_count == 30)
	{
		scene_num = change_scene_to;
	}
	if (change_scene_count <= 30)change_scene_fade -= 0.03;
	change_scene_count--;
}
void myScene::change_scene_draw()
{
	Rect(0, 0, Scene::Size().x, Scene::Size().y).draw(ColorF(0.0, 0.0, 0.0, change_scene_fade));
}
