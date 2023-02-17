# include"myCamera.h"

myCamera::myCamera()
{
	ground_rect.push_back(RectF(Arg::center(1200, 750), 1600, 500));
}


void myCamera::scroll(Vec2 v)
{
	//scaleの更新
	if (true)
	{
		double r = 0.9;
		scale += (r - scale) / 1;
	}
	//centerの更新
	if (true)
	{
		//強制横スクロール
		center += v;
	}

	//戻れないタイプの横スクロール
	if (true)
	{
		limit_camera_min.x = center.x;
		limit_stage_min.x = Max(limit_stage_min.x, center.x - 1920 / 2);
	}

}
void myCamera::set(Vec2 v)
{
	Vec2 min = v;
	Vec2 max = v;

	min.x = Max(min.x, limit_camera_min.x);
	min.x = Min(min.x, limit_camera_max.x);
	max.x = Max(max.x, limit_camera_min.x);
	max.x = Min(max.x, limit_camera_max.x);

	min.y = Max(min.y, limit_camera_min.y);
	min.y = Min(min.y, limit_camera_max.y);
	max.y = Max(max.y, limit_camera_min.y);
	max.y = Min(max.y, limit_camera_max.y);

	//scaleの更新
	if (true)
	{
		double r = Min((max.x - min.x) / std_width, (max.y - min.y) / std_height);
		r = Max(r, 1 / max_scale);
		r = Min(r, 1 / min_scale);
		r = 1.0 / r;
		scale += (r - scale) / 1;
	}

	//centerの更新
	if (true)
	{
		//カメラのセンターが遅れすぎないようにリミッターをかけたい
		center += ((min + max) / 2.0 - center) / 1.0;


	}

	//戻れないタイプの横スクロール
	if (true)
	{
		limit_camera_min.x = center.x;
		limit_stage_min.x = Max(limit_stage_min.x, center.x - 1920 / 2);
	}

}
void myCamera::set(Array<Vec2> vs)
{
	//vs:Vec2の配列という意味
	Vec2 min{ 0,0 };
	Vec2 max{ 0,0 };
	for (int i = 0; i < vs.size(); i++)
	{
		if (i == 0)
		{
			min = vs[0];
			max = vs[0];
		}
		else
		{
			min.x = Min(min.x, vs[i].x);
			min.y = Min(min.y, vs[i].y);
			max.x = Max(max.x, vs[i].x);
			max.y = Max(max.y, vs[i].y);
		}
	}
	min.x = Max(min.x, limit_camera_min.x);
	max.x = Min(max.x, limit_camera_max.x);
	min.y = Max(min.y, limit_camera_min.y);
	max.y = Min(max.y, limit_camera_max.y);

	//scaleの更新
	if (false)
	{
		double r = Min((max.x - min.x) / std_width, (max.y - min.y) / std_height);
		r = Max(r, 1 / max_scale);
		r = Min(r, 1 / min_scale);
		r = 1.0 / r;
		scale += (r - scale) / 30;
	}

	//centerの更新
	if (true)
	{
		//カメラのセンターが遅れすぎないようにリミッターをかけたい
		center += ((min + max) / 2.0 - center) / 20.0;
	}
	

}

void myCamera::draw_stage_area()
{
	//RectF(Arg::center((limit_camera_max + limit_camera_min) / 2), limit_camera_max - limit_camera_min).movedBy(-center).scaledAt({ 0,0 }, scale).movedBy(Scene::Center()).drawFrame(10 * scale, Palette::White);

	//RectF(Arg::center((limit_stage_max + limit_stage_min)/2), limit_stage_max - limit_stage_min).movedBy(-center).scaledAt({ 0,0 }, scale).movedBy(Scene::Center()).drawFrame(10 * scale, Palette::White);
	get_limit_stage().movedBy(-center).scaledAt({ 0,0 }, scale).movedBy(Scene::Center()).drawFrame(10 * scale, Palette::White);
}

