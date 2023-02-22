# include <Siv3D.hpp> // OpenSiv3D v0.6.3
# include "myScene.h"
#include"AssetTexture.h"

//0215Kasai

//bottom2
void Main()
{
	// Windowのサイズ設定
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetResizeMode(ResizeMode::Keep);

	Window::Resize(1280, 720);
	Scene::Resize(1920, 1080);

	// 背景の色を設定 | Set background color
	Scene::SetBackground(Palette::Lightskyblue);

	asset_texture();

	////
	//シーン管理
	myScene myscene;
	//asset_texture();

	bool is_pause = false;

	while (System::Update())
	{
		ClearPrint();
		if (KeyP.down()) {
			is_pause = not is_pause;
		}
		if (not is_pause) {
			myscene.update();
		}
		

		myscene.draw();

	}
}
