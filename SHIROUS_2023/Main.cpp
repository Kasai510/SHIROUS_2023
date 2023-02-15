# include <Siv3D.hpp> // OpenSiv3D v0.6.3
# include "myScene.h"
#include"Asset_texture.h"

//0215Kasai


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


	while (System::Update())
	{
		myscene.update();

		myscene.draw();

	}
}
