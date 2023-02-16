#include "stdafx.h"
#include "EnemyColonyPikaia.h"
#include"EnemyPikaia.h"

EnemyColonyPikaia::EnemyColonyPikaia(Battle* battle):
	EnemyColony(battle)
{

	enemys << std::make_shared<EnemyPikaia>(battle, Vec2(0, 0));
	enemys << std::make_shared<EnemyPikaia>(battle, Vec2(100, 100));
}
