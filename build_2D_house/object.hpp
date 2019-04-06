#pragma once
#include <types.hpp>
#include <vector>
#include <vec_matr.hpp>

using namespace std;

//rotate angle in radians
const float ROTATE_ANGLE = 0.005 ;
const float MOVE_UNIT = 1;

typedef struct{
	int x;
	int y;
} objPoint;
typedef struct{
	objPoint pos;
	double angle;
}objPosition;

class object{
protected:
	//all points are described in model view
	vector<vect2d_h> points;
	//transformation matrix which finally transforms model points to world points
	matr3x2		world_matr;
	struct{
		uint8_t mleft:1;
		uint8_t mright:1;
		uint8_t mup:1;
		uint8_t mdown:1;
		uint8_t rleft:1;
		uint8_t rright:1;
		uint8_t pend:2;
	} state;

public:
	opcode rotate_left();
	opcode rotate_right();
	opcode move_left();
	opcode move_right();
	opcode move_up();
	opcode move_down();
	opcode stop_rotate_left();
	opcode stop_rotate_right();
	opcode stop_move_left();
	opcode stop_move_right();
	opcode stop_move_up();
	opcode stop_move_down();
	opcode update_state();

	opcode dbg_print_all(const string& str) const;
	objPosition get_obj_position() const;
	virtual objPosition get_position() const = 0;
	opcode set_points(const vector<vect2d_h>& vec);
	const vector<vect2d_h>& get_points() const; 
	opcode set_world_matr(const matr3x2&);
	const matr3x2& get_world_matr() const;


	object();
	virtual ~object();

};

class roof : public object{
public:
	virtual objPosition get_position() const;
	roof();
	~roof();
};

class door : public object{
public:
	virtual objPosition get_position() const;
	door();
	virtual ~door();
};

class wall : public object{
public:
	virtual objPosition get_position() const;
	wall();
	virtual ~wall();
};