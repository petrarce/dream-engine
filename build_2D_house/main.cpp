#include <iostream>
#include <world.hpp>
#include <types.hpp>
#include <gui_window.hpp>

using namespace std;

int main(){

	world& world = *world::get_instance();
	gui_window& gui = *gui_window::get_instance();

	if(gui.init() != STATUS_OK){
		pr_err("failed to initialise gui");
		return -1;
	}
	if(world.init() != STATUS_OK){
		pr_err("failed to initialise world");
		return -1;
	}
	usrInp inp = NO_INP;
	while(inp != EXIT){
		gui.render_clear();
		world.update_acrive_object(inp);
		world.deploy_renderer();
		gui.render_scene();
		inp = gui.get_usr_input();
	}
	return 0;
}