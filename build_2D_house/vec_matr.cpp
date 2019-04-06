#include <iostream>
#include <vec_matr.hpp>
#include <cmath>
#include <cstring>

using namespace std;


float vect2d_h::get_x() const
{
	return x;
}
float vect2d_h::get_y() const
{
	return y;
}
vect2d_h::vect2d_h(float nx, float ny):
	x(nx),
	y(ny)
{}

vect2d_h::~vect2d_h()
{
}

void matr3x2::pr_world_matr() const{
	fprintf(stderr, "%3f %3f\n", this->matr[0][0], this->matr[0][1]);
	fprintf(stderr, "%3f %3f\n", this->matr[1][0], this->matr[1][1]);
	fprintf(stderr, "%3f %3f\n", this->matr[2][0], this->matr[2][1]);
	return;
}
matr3x2::matr3x2(float rad_ang, offset_t offs){
	this->matr[0][0] = this->matr[1][1] = cos(rad_ang);
	this->matr[1][0] = sin(rad_ang);
	this->matr[0][1] = -this->matr[1][0];
	this->matr[2][0] = offs.x;
	this->matr[2][1] = offs.y;
}
matr3x2::matr3x2(float new_matr[3][2])
{
	memcpy(this->matr, new_matr, 3*2*sizeof(float));
}

matr3x2::~matr3x2(){}

const vect2d_h operator*(const matr3x2& m, const vect2d_h& v)
{
	return vect2d_h(m.matr[0][0]*v.get_x()+m.matr[1][0]*v.get_y()+m.matr[2][0],
					m.matr[0][1]*v.get_x()+m.matr[1][1]*v.get_y()+m.matr[2][1]);
}
const matr3x2 operator*(const matr3x2& m1, const matr3x2& m2)
{
	float arr[3][2];
	arr[0][0] = m1.matr[0][0]*m2.matr[0][0] + m1.matr[0][1]*m2.matr[1][0];
	arr[0][1] = m1.matr[0][0]*m2.matr[0][1] + m1.matr[0][1]*m2.matr[1][1];
	arr[1][0] = m1.matr[1][0]*m2.matr[0][0] + m1.matr[1][1]*m2.matr[1][0];
	arr[1][1] = m1.matr[1][0]*m2.matr[0][1] + m1.matr[1][1]*m2.matr[1][1];
	arr[2][0] = m1.matr[2][0] + m2.matr[2][0];
	arr[2][1] = m1.matr[2][1] + m2.matr[2][1];
	matr3x2 m(arr);
	return m;
}

double get_vec_magn(const vect2d_h& v)
{
	float x = v.get_x();
	float y = v.get_y();
	return sqrt(x*x + y*y);
}

const double operator*(const vect2d_h& v1, const vect2d_h& v2)
{
	return v1.get_x()*v2.get_x() + v1.get_y()*v2.get_y();
}

const vect2d_h operator-(const vect2d_h& v1, const vect2d_h& v2)
{
	return vect2d_h(v1.get_x() - v2.get_x(), v1.get_y() - v2.get_y());
}

const char operator^(const vect2d_h& v1, const vect2d_h& v2)
{
	float z = v1.get_x()*v2.get_y() - v1.get_y()*v2.get_x();
	if(z>0){
		return 1;
	}
	if(z<0){
		return -1;
	}
	return 0;
}