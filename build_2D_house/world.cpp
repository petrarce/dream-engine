#include <iostream>
#include <world.hpp>
#include <gui_window.hpp>

using namespace std;
opcode world::set_active_obj(worldObj obj_num)
{
	this->active_obj->clear_state();
	this->active_obj = obj_list[obj_num];
	return STATUS_OK;
}

opcode world::update_arrow_obj(){
	matr3x2 act_obj_world_matr = this->active_obj->get_world_matr();
	act_obj_world_matr.matr[0][0] = 1;
	act_obj_world_matr.matr[0][1] = 0;
	act_obj_world_matr.matr[1][0] = 0;
	act_obj_world_matr.matr[1][1] = 1;
	this->arrow_obj->set_world_matr(act_obj_world_matr);
	return STATUS_OK;
}

world* world::get_instance()
{
	static world instance;
	return &instance;
}

opcode world::update_acrive_object(usrInp& in)
{
	switch(in){
		case SWIRCH_ROOF:
		if(obj_list[ROOF] != this->active_obj){
			set_active_obj(ROOF);
		}
		break;

		case SWITCH_DOOR:
		if(obj_list[DOOR] != this->active_obj){
			set_active_obj(DOOR);
		}
		break;

		case SWITCH_WALL:
		if(obj_list[WALL] != this->active_obj){
			set_active_obj(WALL);
		}
		break;

		case ROTATE_LEFT:
		this->active_obj->rotate_left();
		break;

		case ROTATE_RIGHT:
		this->active_obj->rotate_right();
		break;

		case MOVE_LEFT:
		this->active_obj->move_left();
		break;

		case MOVE_RIGHT:
		this->active_obj->move_right();
		break;

		case MOVE_UP:
		//SDL has reversed x axis so down and up event was changed
		this->active_obj->move_down();
		break;

		case MOVE_DOWN:
		//SDL has reversed x axis so down and up event was changed
		this->active_obj->move_up();
		break;

		case STOP_ROTATE_LEFT:
		this->active_obj->stop_rotate_left();
		break;

		case STOP_ROTATE_RIGHT:
		this->active_obj->stop_rotate_right();
		break;

		case STOP_MOVE_LEFT:
		this->active_obj->stop_move_left();
		break;

		case STOP_MOVE_RIGHT:
		this->active_obj->stop_move_right();
		break;

		case STOP_MOVE_UP:
		this->active_obj->stop_move_down();
		break;

		case STOP_MOVE_DOWN:
		this->active_obj->stop_move_up();
		break;

		case NO_INP:
		break;
		
		case EXIT:
		break;

		default:
		pr_warn("invalid user input...");
		break;
	}
	this->active_obj->update_state();
	this->update_arrow_obj();
	return STATUS_OK;
}

opcode world::deploy_renderer()
{
	gui_window& gui = *gui_window::get_instance();
	gui_window::guiTextureIndex i = 1;
	for(const object* obj : obj_list){
		objPosition pos = obj->get_position();
		gui.render_texture(obj->get_texture_path(), SDL_Point({pos.pos.x, pos.pos.y}), pos.angle);
	}
	return STATUS_OK;
}

opcode world::init()
{

	gui_window& gui = *gui_window::get_instance();
	
	object* roof_obj = new object("./roof.png");
	object* wall_obj = new object("./wall.png");
	object* door_obj = new object("./door.png");
	object* arrow_obj = new object("./arrow.png");

	this->active_obj = roof_obj;
	this->arrow_obj = arrow_obj;
	obj_list.push_back(roof_obj);
	obj_list.push_back(wall_obj);
	obj_list.push_back(door_obj);
	obj_list.push_back(arrow_obj);


	gui.loadTexture(roof_obj->get_texture_path());
	gui.loadTexture(door_obj->get_texture_path());
	gui.loadTexture(wall_obj->get_texture_path());
	gui.loadTexture(arrow_obj->get_texture_path());

	return STATUS_OK;
}

opcode world::deinit()
{
	for(object* obj : this->obj_list){
		delete obj;
	}
	obj_list.clear();
	return STATUS_OK;
}

world::world()
{

}

world::~world()
{
	deinit();
}