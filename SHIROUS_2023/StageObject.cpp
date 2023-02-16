﻿#include"StageObject.h"

Stage_object::Stage_object(Vec2 p, double w, double h)
{
	pos = p;
	pre_pos = pos;
	width = w;
	height = h;
}

void Stage_object::update()
{

}

void Stage_object::draw(myCamera camera)
{
	get_rect().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).draw(Palette::Blue);
}