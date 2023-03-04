#include"StageObject.h"

Stage_object::Stage_object(Battle* battle, Vec2 p, double w, double h):BattleObject(battle)
{
	pos = p;
	pre_pos = pos;
	width = w;
	height = h;
	draw_order = 10;
}

Stage_object::Stage_object(Battle* battle, const Rect& rect) :BattleObject(battle)
{
	pos = rect.center();
	pre_pos = pos;
	width = rect.size.x;
	height = rect.size.y;
	draw_order = 10;
}

void Stage_object::update()
{

}

void Stage_object::draw(myCamera camera)
{
	//get_rect().movedBy(-camera.get_center()).scaledAt({ 0,0 }, camera.get_scale()).movedBy(Scene::CenterF()).draw(Palette::Blue);
	camera.draw_texture(get_rect(), Color(80,40,20));
}
