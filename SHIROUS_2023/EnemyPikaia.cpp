#include "stdafx.h"
#include "EnemyPikaia.h"

EnemyPikaia::EnemyPikaia(Battle* battle,Vec2 p):Enemy(battle, p)
{
	image_name = U"pikaia";
	width = 250;
	height = 100;
}

void EnemyPikaia::update()
{

}

