#include "stdafx.h"
#include "EnemyColony.h"
#include"Battle.h"

EnemyColony::EnemyColony(Battle* battle)
{
	this->battle = battle;
}

void EnemyColony::update()
{
	for (auto enemy : enemys) {
		enemy->update();
	}
}

void EnemyColony::draw()
{
	for (auto enemy : enemys) {
		enemy->draw();
	}
}
