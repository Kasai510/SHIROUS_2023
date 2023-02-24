#pragma once
#include "stdafx.h"

class myCamera
{
private:
	Vec2 center = { 1920/2,1080/2 };//中心座標
	double scale = 0.9;//拡大・縮小倍率。今回は１で固定。開発時は0.9で描画範囲を広げる。
	double min_scale = 0.9;//最小縮小倍率(min_scale倍で描画されるので、1/min_scale倍の範囲が描画される)
	double max_scale = 0.9;//最大拡大倍率(max_scale倍で描画されるので、1/max_scale倍の範囲が描画される)
	double std_width = 1200.0;//scaleが１になるときの幅
	double std_height = 550.0;//scaleが１になるときの幅

	
	//これ以上はカメラワークが追いかけない
	Vec2 limit_camera_min = { 1920 / 2, 1080 / 2 };		//カメラワーク限界の左上の座標
	Vec2 limit_camera_max = { 19200,1080 / 2 };		//カメラワーク限界の右下の座標
	//ステージ限界の座標。
	Vec2 limit_stage_min = { 0, 0 };			//ステージ限界の左上の座標
	Vec2 limit_stage_max = { 19200,1080 };		//ステージ限界の右下の座標

	Array<RectF> ground_rect;//stageの地面の情報。画面の縦揺れの軽減に使う。

	Mat3x2 mat;

	inline void calc_mat();

public:
	myCamera();
	void scroll(Vec2 v);
	void set(Vec2 v);
	void set(Array<Vec2> vs);
	void set_center(Vec2 c) { center = c; }
	void set_scale(double s) { scale = s; }
	void set_camera_max(Vec2 v) { limit_camera_max = v; }
	void set_camera_min(Vec2 v) { limit_camera_min = v; }
	Vec2 get_center() { return center; }
	double get_scale() { return scale; }
	Vec2 get_limit_stage_min() { return limit_stage_min; }
	Vec2 get_limit_stage_max() { return limit_stage_max; }
	RectF get_limit_stage() { return RectF(Arg::center((limit_stage_min + limit_stage_max) / 2), limit_stage_max - limit_stage_min); }
	
	void draw_stage_area();

	void draw_texture(const auto& tex, const Vec2& p) {
		Transformer2D tf{ mat };
		tex.drawAt(p);
	}
	void draw_texture(const auto& drawable,Color color) {
		Transformer2D tf{ mat };
		drawable.draw(color);
	}
	bool in_camera(const auto& obj) {
		RectF camera_rect{ Arg::center(center),1920,1080};
		return camera_rect.intersects(obj);
	}

	Vec2 windowpos_in_camera(Vec2 wp) {
		return (wp - Scene::CenterF()) / scale + center;
	}
	
};


