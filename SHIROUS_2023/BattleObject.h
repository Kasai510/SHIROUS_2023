#pragma once
class BattleObject//:public std::enable_shared_from_this<BattleObject>
{
public:
	BattleObject(class Battle* battle);
	Battle* battle;
	double draw_order=5;
};

