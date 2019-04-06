#include <iostream>
#include <object.hpp>
#include <cmath>

using namespace std;

opcode object::rotate_left(){ this->state.rleft = 1; return STATUS_OK;}
opcode object::rotate_right(){ this->state.rright = 1; return STATUS_OK;}
opcode object::move_left(){ this->state.mleft = 1; return STATUS_OK;}
opcode object::move_right(){ this->state.mright = 1; return STATUS_OK;}
opcode object::move_up(){ this->state.mup = 1; return STATUS_OK;}
opcode object::move_down(){ this->state.mdown = 1; return STATUS_OK;}
opcode object::stop_rotate_left(){ this->state.rleft = 0; return STATUS_OK;}
opcode object::stop_rotate_right(){ this->state.rright = 0; return STATUS_OK;}
opcode object::stop_move_left(){ this->state.mleft = 0; return STATUS_OK;}
opcode object::stop_move_right(){ this->state.mright = 0; return STATUS_OK;}
opcode object::stop_move_up(){ this->state.mup = 0; return STATUS_OK;}
opcode object::stop_move_down(){ this->state.mdown = 0; return STATUS_OK;}

opcode object::update_state()
{
	matr3x2 rot(this->state.rleft*ROTATE_ANGLE - this->state.rright*ROTATE_ANGLE, 
					{	this->state.mright*MOVE_UNIT - this->state.mleft*MOVE_UNIT,
						this->state.mup*MOVE_UNIT - this->state.mdown*MOVE_UNIT
					});
	this->world_matr = this->world_matr *  rot;
	return STATUS_OK;
}

opcode object::dbg_print_all(const string& str) const
{
	int i = 0;
	for(const vect2d_h& model_pt : this->points){
		vect2d_h world_point = this->world_matr * model_pt;
		pr_dbg("%s p%d: x=%.3f, y=%.3f", str.c_str(), i++, world_point.get_x(), world_point.get_y());
	}
	pr_dbg("p1-p2 distance: %.3f", sqrt(	pow(this->points[0].get_x() - this->points[1].get_x(),2) + 
										pow(this->points[0].get_y() - this->points[1].get_y(),2)));
	this->world_matr.pr_world_matr();
	return STATUS_OK;
}

objPosition object::get_obj_position() const
{
	vect2d_h position = this->world_matr * this->points[0];
	vect2d_h rotated = (this->world_matr * this->points[1]) - position;
	vect2d_h origin(0,1);
	double dorProd = origin*rotated;
	int sign = (dorProd > 0)?1:-1;
	double angle = (origin^rotated) * 57 * acos(
						dorProd
									/
				(get_vec_magn(origin)*get_vec_magn(rotated))
	);

	pr_dbg("angle=%.3f", angle);

	objPosition thisPos = {
		{	(int) position.get_x(),
			(int) position.get_y()},
		angle
	};
	return thisPos;
}

opcode object::set_points(const vector<vect2d_h>& vec){
	this->points = vec;
	return STATUS_OK;
}

const vector<vect2d_h>& object::get_points() const
{
	return this->points;
}

opcode object::set_world_matr(const matr3x2& m)
{
	this->world_matr = m;
	return STATUS_OK;
}

const matr3x2& object::get_world_matr() const
{
	return this->world_matr;
}

object::object():
	world_matr(0, {0,0}),
	state({0,0,0,0,0,0,0})
{
	vect2d_h pt1(0, 0);
	vect2d_h pt2(0, 1);
	this->points.push_back(pt1);
	this->points.push_back(pt2);
}

object::~object()
{

}

objPosition roof::get_position() const
{
	//dbg_print_all(string("roof"));
	return get_obj_position();
}
roof::roof()
{
	world_matr = matr3x2(0, {3*MOVE_UNIT, 4*MOVE_UNIT});
}
roof::~roof(){}

objPosition door::get_position() const
{
	//dbg_print_all(string("door"));
	return get_obj_position();
}
door::door()
{
	world_matr = matr3x2(0, {10*MOVE_UNIT, -3*MOVE_UNIT});
}
door::~door(){}

objPosition wall::get_position() const
{
	//dbg_print_all(string("wall"));
	return get_obj_position();
}
wall::wall()
{
	world_matr = matr3x2(0, {3*MOVE_UNIT, 2*MOVE_UNIT});
}
wall::~wall(){}