#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <boost/stacktrace.hpp>

using namespace std;

#ifdef DEBUG
#undef assert
#define assert(exp) { \
	if(!(exp)) { \
		pr_dbg("assertion failes: %s", #exp); \
		cout << boost::stacktrace::stacktrace(); \
		exit(-1); \
	} \
}

#define pr_dbg(msg, args...) printf("[%s:%d] " msg "\n", __FILE__, __LINE__, ##args)
#else
#define pr_dbg(msg, args...) 
#define assert(expr) 
#endif

enum TYPE_VECTOR{
	VECTOR_CARTESIAN = 0,
	VECTOR_SPHERICAL,
	VECTOR_CYLINDRICAL,
};

enum opcode{
	STATUS_OK = 0,
	STATUS_NOK
};