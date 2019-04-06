#pragma once
#include <iostream>

#define pr_dbg(msg, args...) fprintf(stderr, 	"[DEBUG](%s:%d)" msg "\n", __FILE__, __LINE__, ##args)
#define pr_err(msg, args...) fprintf(stderr, 	"[ERROR]" msg "\n", ##args)
#define pr_warn(msg, args...) fprintf(stderr, 	"[WARNING]" msg "\n", ##args)



enum opcode{
	STATUS_OK,
	STATUS_NOK
};

enum usrInp{
		SWIRCH_ROOF,
		SWITCH_DOOR,
		SWITCH_WALL,
		ROTATE_LEFT,
		ROTATE_RIGHT,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		STOP_ROTATE_LEFT,
		STOP_ROTATE_RIGHT,
		STOP_MOVE_LEFT,
		STOP_MOVE_RIGHT,
		STOP_MOVE_UP,
		STOP_MOVE_DOWN,
		NO_INP,
		EXIT,
};