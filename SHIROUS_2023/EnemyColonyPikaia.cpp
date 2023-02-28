#include "stdafx.h"
#include "EnemyColonyPikaia.h"
#include"EnemyPikaia.h"
#include"EnemyHallucigenia.h"

EnemyColonyPikaia::EnemyColonyPikaia(Battle* battle):
	EnemyColony(battle)
{

	//enemys << std::make_shared<EnemyPikaia>(battle, Vec2(2100,500));
	enemys << std::make_shared<EnemyPikaia>(battle, Vec2(2000, 400));
	enemys << std::make_shared<EnemyHallucigenia>(battle, Vec2(2000, 600));
}
