#pragma once
#include <iostream>
#include <vector>
#include <object.hpp>
#include <types.hpp>

using namespace std;

class world{

	enum worldObj{
		ROOF = 0,
		DOOR,
		WALL
	};

private:
	vector<object*> obj_list;
	object* active_obj;
	object* arrow_obj;

	opcode set_active_obj(worldObj);
	opcode update_arrow_obj();
public:
	static world* get_instance();
	opcode update_acrive_object(usrInp&);
	opcode deploy_renderer();
	opcode init();
	opcode deinit();


private:
	//deleted operators
	world();
	~world();
	world(world&){};
	world& operator=(world&){return *this;};

};