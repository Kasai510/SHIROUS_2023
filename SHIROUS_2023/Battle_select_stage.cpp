#include"Battle.h"

void Battle::init_select_stage()
{

}

void Battle::update_select_stage()
{
	if (KeyEnter.down())
	{
		change_battle_scene(Battle_Scene::battle);
	}

	if(stage_index % stage_select_rect_num == 0)
	{
		//stage_indexが4の倍数
		if (KeyDown.down())
		{
			//下の段にいく
			stage_index++;
			
		}

		if (int(stage_index / stage_select_rect_num) % 2 == 0)
		{
			//stage_indexが8,16,・・・
			if (KeyRight.down())
			{
				stage_index--;
				
			}
		}
		else
		{
			
			//stage_indexが4,12,・・・
			if (KeyLeft.down())
			{
				stage_index--;
				
			}
		}
	}
	else
	{
		//stage_indexが４の倍数でない
		
		if (stage_index % stage_select_rect_num == 1)
		{
			//stage_indexが4で割ると１の数5,9,

			if (KeyUp.down())
			{
				stage_index--;
				
			}
		}


		if (int(stage_index / stage_select_rect_num) % 2 == 0)
		{
			//4で割ると商が偶数の時1,2,3,9,10


			if (KeyRight.down())
			{
				if (stage_index <= clear_stage)
				{
					//現在いる位置のステージをクリアしているなら
					stage_index++;
					
				}
			}

			if (KeyLeft.down())
			{
				stage_index--;
				
			}
		}
		else
		{
			//4で割ると商が奇数の時1,2,3,9,10

			if (KeyLeft.down())
			{
				if (stage_index <= clear_stage)
				{
					//現在いる位置のステージをクリアしているなら
					stage_index++;
					
				}
			}

			if (KeyRight.down())
			{
				stage_index--;
	
			}
		}
	}


	stage_index = Max(1, stage_index);
	stage_index = Min(stage_num, stage_index);
}

void Battle::draw_select_stage()
{
	//背景
	background.draw();
	font90(stage_index).drawAt(scene_size / 2);

	for (int i = 0; i < stage_num; i++)
	{
		int box_set_x;
		//レベル選択用の四角形
		if (int(i / stage_select_rect_num) % 2 == 0)
		{
			box_set_x = 200 + int(i % stage_select_rect_num) * 500;//boxの中央のx座標
		}
		else
		{
			box_set_x = 1700 + int(i % stage_select_rect_num) * -500;
		}
		int box_set_y = 200 + 300 * int(i / stage_select_rect_num);

		Rect tex_rect(Arg::center(box_set_x, box_set_y), 400, 200);

		if (i <= clear_stage)
		{
			tex_rect.draw(Palette::Skyblue);
		}
		else
		{

			tex_rect.draw(Palette::Grey);
		}


		if (i == stage_index-1)
		{
			tex_rect.drawFrame(2, Palette::Red);
		}

		font50(i + 1).drawAt(tex_rect.center(), Palette::White);

	}
}
