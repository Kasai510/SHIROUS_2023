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
	TextureAsset::Register(U"pikaia_shot_white", Resource(U"data/image/fish/pikaia/pikaia_shot_white.png"));
	TextureAsset::Register(U"kurage", Resource(U"data/image/fish/kurage/kurage.png"));
	TextureAsset::Register(U"seahorse", Resource(U"data/image/fish/seahorse/seahorse.png"));
	TextureAsset::Register(U"hallucigenia", Resource(U"data/image/fish/hallucigenia/hallucigenia.png"));
	TextureAsset::Register(U"hallucigenia_shot", Resource(U"data/image/fish/hallucigenia/hallucigenia_shot.png"));
	TextureAsset::Register(U"opabinia", Resource(U"data/image/fish/opabinia/opabinia.png"));
	TextureAsset::Register(U"opabinia_mouth_close", Resource(U"data/image/fish/opabinia/opabinia_mouth_close.png"));
	TextureAsset::Register(U"opabinia_mouth_open", Resource(U"data/image/fish/opabinia/opabinia_mouth_open.png"));
	TextureAsset::Register(U"opabinia_shot", Resource(U"data/image/fish/opabinia/opabinia_shot.png"));

	TextureAsset::Register(U"poseidon", Resource(U"data/image/fish/poseidon/poseidon.png"));
	TextureAsset::Register(U"poseidonshot0", U"data/image/fish/poseidon/poseidonshot0.png");
	TextureAsset::Register(U"poseidonshot1", U"data/image/fish/poseidon/poseidonshot1.png");

	TextureAsset::Register(U"harisenbong", Resource(U"data/image/fish/harisenbong/ハリセンボン.png"));
	TextureAsset::Register(U"harisenbongshot", Resource(U"data/image/fish/harisenbong/ハリセンボンショット.png"));

	TextureAsset::Register(U"annkou", Resource(U"data/image/fish/annkou/アンコウ.png"));
	TextureAsset::Register(U"annkou_attack_effect", Resource(U"data/image/fish/annkou/アンコウエフェクト.png"));



	TextureAsset::Register(U"rock_1", U"data/image/object/rock/rock_1.png");
	TextureAsset::Register(U"kaimen_1", U"data/image/object/living/kaimen_1.png");
	TextureAsset::Register(U"bubble", U"data/image/object/bubble/bubble.png");
}
