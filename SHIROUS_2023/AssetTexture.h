#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void asset_texture()
{
	TextureAsset::Register(U"shirous", Resource(U"data/image/fish/shirous/シラス.png"));
	TextureAsset::Register(U"ika", Resource(U"data/image/fish/shirous/イカ.png"));
	TextureAsset::Register(U"pikaia", Resource(U"data/image/fish/pikaia/pikaia.png"));
}
