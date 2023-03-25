#pragma once
#include "Enemy.h"



class EnemyAnomalocaris :
    public Enemy
{
private:
	//行動の種類
	enum  Motion_Kind
	{
		motion_kind_standby = 0,//待機
		motion_kind_hurtle,//突進
		motion_kind_shot1,//普通の弾

		motion_kind_num//kindの合計
	};


	Array<Array<Motion_Kind>> motion_patarns;//モーションパターンの種類
	int now_motion_patarn_index;//1つのモーションパターン内のindex
	int now_motion_patarn_num;//1つのモーションパターン内のモーションの数

	int now_motion_patarns_index;//全てのモーションパターンのindex
	int motion_patarns_num;//全てのモーションパターンの総数

	Motion_Kind now_motion_kind{ motion_kind_standby };

	//motionを動かすときに様々な用途で使用する
	double motion_timer{ 0.0 };
	int motion_counter{ 0 };
	int motion_phase{ 0 };
	bool motion_bool{ false };
	Vec2 start_pos;

public:
	EnemyAnomalocaris(Battle* battle, const Vec2& p);
	void update();
	void move() {};//つかう？
	void create_motion_patarn();

	void move_intersect_stage(Stage_object stage) {};
	void draw();

	void change_motion(Motion_Kind next_motion_kind);//モーションの変更に使用
	void change_motion();//モーションの変更に使用
	void change_motion_patarn();

	void init_motion();
	void update_motion();
	void draw_motion();

	
	


	//待機
	void init_motion_standby();
	void update_motion_standby();
	void draw_motion_standby();

	//突進
	void init_motion_hurtle();
	void update_motion_hurtle();
	void draw_motion_hurtle();
	
	//普通の弾
	void init_motion_shot1();
	void update_motion_shot1();
	void draw_motion_shot1();
};

