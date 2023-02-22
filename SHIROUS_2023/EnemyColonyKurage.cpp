#include "stdafx.h"
#include "EnemyColonyKurage.h"
#include"EnemyKurage.h"

EnemyColonyKurage::EnemyColonyKurage(Battle* battle):EnemyColony(battle)
{
	enemys << std::make_shared<EnemyKurage>(battle, Vec2(1700, 400));
}
