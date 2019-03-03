#pragma once
#include <iostream>
#include <types.hpp>

using namespace std;

namespace dream_vector3d{

	class vector3d_cartesian
	{
	private:
		vector<int32_t> coordinates;
		mutable double _magnitude;

		double compute_magnitude() const;
	public:
		int32_t	 get_X() const;
		int32_t	 get_Y() const;
		int32_t	 get_Z() const;
		const vector<int32_t>& get_vector() const;
		opcode	 set_X(int32_t);
		opcode	 set_Y(int32_t);
		opcode	 set_Z(int32_t);


		opcode normalise();
		double get_magnitude() const;
		vector3d_cartesian larp(vector3d_cartesian&, vector3d_cartesian&){return vector3d_cartesian();};
		//spheric_from_cart();
		//cylindric_from_cart();


	public:
		vector3d_cartesian();
		vector3d_cartesian(int32_t, int32_t,  int32_t);
		~vector3d_cartesian();


	public:
		const vector3d_cartesian& operator*=(int32_t);
		const vector3d_cartesian& operator+=(const vector3d_cartesian&);
		const vector3d_cartesian& operator-=(const vector3d_cartesian&);

	};

	const vector3d_cartesian operator*(int32_t, const vector3d_cartesian&);
	const vector3d_cartesian operator*(const vector3d_cartesian&, int32_t);
	const int32_t operator*(const vector3d_cartesian&, const vector3d_cartesian&);
	const vector3d_cartesian operator^(const vector3d_cartesian&, const vector3d_cartesian&);
	const vector3d_cartesian operator+(const vector3d_cartesian&, const vector3d_cartesian&);
	const vector3d_cartesian operator-(const vector3d_cartesian&, const vector3d_cartesian&);
	const bool operator==(const vector3d_cartesian& v1, const vector3d_cartesian& v2);

	double get_angle(const vector3d_cartesian&, const vector3d_cartesian&);



}