#include "stdafx.h"
#include "myIEffectCirclestar.h"
#include"Battle.h"

myIEffectCirclestar::myIEffectCirclestar(Battle* battle, const Vec2& p, const double r):myIEffect(battle)
{
	this->p = p;
	this->r = r;
	
}

void myIEffectCirclestar::update()
{
	if (time == 30) {
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
