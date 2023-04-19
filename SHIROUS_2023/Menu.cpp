#include"Menu.h"

void Menu::update()
{
	double deltaTime = Scene::DeltaTime();

	if (!instruction)
	{
		if (KeyUp.down())
		{
			sellect = 0;
		}
		else if (KeyDown.down())
		{
			sellect = 1;
		}
		if (KeyEnter.down())
		{
			if (sellect == 0) change_scene_to = 2;
			else if (sellect == 1) instruction = true;
		}
	}
	else
	{
		if (KeyEnter.down())
		{
			instruction = false;
		}
	}

}

void Menu::draw()
{
	//タイトル画面の画像(未実装)
	font100(U"SHIROUS").drawAt(Scene::Center().movedBy(0,-300), Palette::White);
	font100(U"SHIROUS").drawAt(Scene::Center().movedBy(-3,-303), Palette::Black);


	if (!instruction)
	{
		if (sellect == 0)
		{
			font50(U"ゲームスタート").drawAt(Scene::Center().movedBy(0, 300).movedBy(2,2), ColorF(1.0, 1.0, 1.0, Min(frame%100,100-frame%100)/50.0));
			Triangle(Scene::Center().movedBy(-200, 295), 35+5.0* Min(frame % 100, 100 - frame % 100) / 50.0, 180_deg).draw(Palette::White);
		}
		else if (sellect == 1)
		{
			font50(U"操作練習").drawAt(Scene::Center().movedBy(0, 400).movedBy(2, 2), ColorF(1.0, 1.0, 1.0, Min(frame % 100, 100 - frame % 100) / 50.0));
			Triangle(Scene::Center().movedBy(-125, 395), 35 + 5.0 * Min(frame % 100, 100 - frame % 100) / 50.0, 180_deg).draw(Palette::White);
		}

		font50(U"ゲームスタート").drawAt(Scene::Center().movedBy(0, 300), Palette::Black);
		font50(U"操作練習").drawAt(Scene::Center().movedBy(0, 400), Palette::Black);

		font50(U"なんかいい感じの背景が欲しい").drawAt(Scene::Center().movedBy(0, 0), Palette::Black);
		
	}

	//操作練習Sceneを実装したい
	if (instruction)
	{
		//font50(U"↑↓←→：移動\n１キー または □ボタン：遠距離攻撃\n２キー または △ボタン：近距離攻撃\n３キー または Rボタン：ガード\n４キー または ×ボタン：回避\n\nEnterで戻る").draw(50, 200, Palette::Black);
		font50(U"未実装").draw(50, 200, Palette::Black);
	}


	frame++;
}

bool Menu::change_scene_check()
{
	if (change_scene_to == -1)return false;
	else return true;
}

int Menu::change_scene()
{
	int i = change_scene_to;
	change_scene_to = -1;
	return i;
}
