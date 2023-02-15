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
	if (!instruction)
	{
		//タイトル画面の画像
		//TextureAsset(U"title1").scaled(0.8).drawAt(Scene::CenterF(), ColorF(1.0, 1.0, 1.0, screen / 30.0));
		//TextureAsset(U"title2").scaled(0.8).drawAt(Scene::CenterF(), ColorF(1.0, 1.0, 1.0, 1.0 - screen / 30.0));
	}


	fontBlack(U"SHIROUS").drawAt(Scene::CenterF().movedBy(0, -300).movedBy(1, 1));
	fontBlack(U"SHIROUS").drawAt(Scene::CenterF().movedBy(0, -300), Palette::Black);

	if (!instruction)
	{
		font50(U"ゲームスタート").drawAt(start_game.center(), Palette::Black);
		font50(U"操作説明").drawAt(start_explain.center(), Palette::Black);
		font50(U"Enterでスタート").drawAt(Scene::CenterF().movedBy(0, 350), Palette::Black);

		if (sellect == 0)
		{
			if ((frame % 100) < 50)start_game.draw(ColorF(1.0, 1.0, 1.0, (frame % 100) / 60.0));
			else start_game.draw(ColorF(1.0, 1.0, 1.0, 5.0 / 6.0 - ((frame - 50) % 100) / 60.0));
		}
		else if (sellect == 1)
		{
			if ((frame % 100) < 50)start_explain.draw(ColorF(1.0, 1.0, 1.0, (frame % 100) / 60.0));
			else start_explain.draw(ColorF(1.0, 1.0, 1.0, 5.0/6.0 - ((frame - 50) % 100) / 60.0));
		}
	}

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
