#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void asset_texture()
{
	TextureAsset::Register(U"シラス（基底）", U"data/image/fish/shirous/シラス.png");
	TextureAsset::Register(U"シラス（派生）", U"data/image/fish/shirous/シラス.png");

	TextureAsset::Register(U"シラス", U"data/image/fish/shirous/シラス.png");
}
