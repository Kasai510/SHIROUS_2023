#pragma once
#include"Enemy.h"

//同じ種類の敵集団を管理する
class EnemyColony
{
protected:
	Array<std::shared_ptr<Enemy>> enemys;
public:
	EnemyColony(Battle* battle);
	void update();
	void draw();
	Array<std::shared_ptr<Enemy>>& get_enemys() {
		return enemys;
	}
private:
	Battle* battle;
};

