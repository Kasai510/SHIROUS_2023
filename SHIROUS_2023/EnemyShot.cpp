#include "stdafx.h"
#include "EnemyShot.h"

EnemyShot::EnemyShot(Battle* battle,const  Vec2& p) :Shot(battle, p)
{

}

void EnemyShot::move()
{
	pos += v;
}
