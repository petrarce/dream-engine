#include <iostream> 
#include <types.hpp>

using namespace std;

typedef struct offset{
	float x;
	float y;
} offset_t;


class vect2d_h{
private:
	float x;
	float y;
public:
	float get_x() const;
	float get_y() const;
	vect2d_h(float, float);
	~vect2d_h();
};

class matr3x2{
public:
	float matr[3][2];
public:
	void pr_world_matr() const;
	matr3x2(float, offset_t);
	matr3x2(float[3][2]);
	~matr3x2();
private:
	matr3x2();
};

//multiplication of homogenous matrix on vector
const vect2d_h operator*(const matr3x2&, const vect2d_h&);
//multiplication 3x2 homogenous marices 
const matr3x2 operator*(const matr3x2&, const matr3x2&);
const matr3x2 operator*=(matr3x2&, const matr3x2&);
//vector magnitude
double get_vec_magn(const vect2d_h&);
//scalar multiplication of vectors
const double operator*(const vect2d_h&, const vect2d_h&);
//vector-vector substraction
const vect2d_h operator-(const vect2d_h&, const vect2d_h&);
//direction of rotatino v1 with respect to v2 based on cross product:
// +1 - anticlocjwise
// -1 - clockwise
// 0 - have the same direction
const char operator^(const vect2d_h&, const vect2d_h&);