#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void asset_texture()
{
	TextureAsset::Register(U"shirous", Resource(U"data/image/fish/shirous/シラス.png"));
	TextureAsset::Register(U"ika", Resource(U"data/image/fish/shirous/イカ.png"));
	TextureAsset::Register(U"pikaia", Resource(U"data/image/fish/pikaia/pikaia.png"));
	TextureAsset::Register(U"pikaia_1", Resource(U"data/image/fish/pikaia/pikaia_1.png"));
	TextureAsset::Register(U"pikaia_2", Resource(U"data/image/fish/pikaia/pikaia_2.png"));
	TextureAsset::Register(U"pikaia_3", Resource(U"data/image/fish/pikaia/pikaia_3.png"));
	TextureAsset::Register(U"pikaia_shot", Resource(U"data/image/fish/pikaia/pikaia_shot.png"));
	TextureAsset::Register(U"kurage", Resource(U"data/image/fish/kurage/kurage.png"));
	TextureAsset::Register(U"seahorse", Resource(U"data/image/fish/seahorse/seahorse.png"));
	TextureAsset::Register(U"poseidon", Resource(U"data/image/fish/poseidon/poseidon.png"));
}
