#include "stdafx.h"
#include "myIEffectCirclestar.h"
#include"Battle.h"

myIEffectCirclestar::myIEffectCirclestar(Battle* battle, const Vec2& p, const double r, const Color color):myIEffect(battle)
{
	this->p = p;
	this->r = r;
	this->color = color;
	
}

myIEffectCirclestar::myIEffectCirclestar(Battle* battle, const Vec2& p, const double r, const double dead_frame, const Color color, std::shared_ptr<Fish> master, bool be_following )
	:myIEffect(battle),master(master)
{
	this->p = p;
	this->r = r;
	this->dead_frame = dead_frame;
	this->color = color;
	this->be_following = be_following;
	
}

void myIEffectCirclestar::update()
{
	if (time == dead_frame) {
		dead = true;
	}
	time++;
}

void myIEffectCirclestar::draw()
{

	myCamera& camera = battle->get_camera();
	Transformer2D tf{ Mat3x2::Translate(Scene::Center() - camera.get_center() + p).scaled(camera.get_scale(), Scene::Center()) };
	Transformer2D tf2{ Mat3x2::Scale(r / 200) };
	//ScopedRenderStates2D blend{ BlendState::Additive };
	const auto& multis = battle->get_circlestar_effect();
	MultiPolygon(multis[Min<int>(time, multis.size() - 1)]).draw(Color(255));
}
