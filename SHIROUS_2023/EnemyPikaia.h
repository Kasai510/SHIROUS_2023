#pragma once
#include "Enemy.h"
class EnemyPikaia :
	public Enemy
{
public:
	EnemyPikaia(Battle* battle,const Vec2& p);

	void update();
	void move();
	void draw();
private:
	Array<TextureRegion> anime;
	Array<int32> delays;
};

