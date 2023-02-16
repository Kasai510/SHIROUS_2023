#pragma once
# include "myCamera.h"
# include "myInput.h"

#include"Fish.h"
#include"Option.h"
#include"Shot.h"
#include"StageObject.h"

class Player : public Fish
{


protected:
	Array<std::shared_ptr<Option>> options;
	
public:

	Player();
	Player(int id, Vec2 pos);
	~Player();

	virtual void update();
	virtual void move();
	virtual void move_intersect_stage(Stage_object stage);
	virtual void check_limit_stage(myCamera camera);

	virtual bool ready_shot();
	virtual std::shared_ptr<Shot> shot();
	virtual bool ready_opt_shot(int index);
	virtual std::shared_ptr<Shot> opt_shot(int index);


	virtual void draw(myCamera camera);
	virtual void draw_back(myCamera camera);
	virtual void draw_front(myCamera camera);


	int get_opt_size() { return options.size(); }
	Option& get_opt(int i) { return *options[i]; }


};
