#pragma once
#include "Fish.h"

enum Enemy_Kind
{
	enemy_kind_pikaia = 0,
	enemy_kind_opabinia,
	enemy_kind_kurage,
	enemy_kind_hallucigenia,
	enemy_kind_anomalocaris,

	enemy_kind_num,
};



class Enemy :
	public Fish//,public std::enable_shared_from_this<Enemy>
{
public:
	Enemy(Battle* battle,const Vec2& p);
	void update();
	void draw();
	virtual void move_intersect_stage(Stage_object stage) ;
	void move();
	int get_enemy_kind() { return enemy_kind; }
	Vec2 get_spon_pos() { return spon_pos; }
	void drop_item();
	void drop_LP();
protected:
	int time = 0;
	Enemy_Kind enemy_kind{ enemy_kind_pikaia };
	Vec2 spon_pos{ 0,0 };
	bool active = false;//画面内に入るまで動かない。
};

