#pragma once
#include <iostream>
#include <types.hpp>

using namespace std;

namespace dream_vector3d{

	class base_vector3d
	{

	public:
		virtual TYPE_VECTOR get_type() = NULL;
		virtual void normalise() = NULL;
		virtual mult_by_sclr(int) = NULL;
		virtual get_magnitude() = NULL;
	};

}