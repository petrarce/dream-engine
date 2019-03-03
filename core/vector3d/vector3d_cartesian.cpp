#include <iostream>
#include <cmath>
#include <vector3d_cartesian.hpp>

using namespace std;
namespace dream_vector3d{

double vector3d_cartesian::compute_magnitude() const
{
	if(this->_magnitude = -1){
		this->_magnitude = 	this->coordinates[0] * this->coordinates[0] + 
							this->coordinates[1] * this->coordinates[1] +
							this->coordinates[2] * this->coordinates[2];
		this->_magnitude = sqrt(this->_magnitude);
	}
	assert(this->_magnitude >= 0);
	return this->_magnitude;
}

int32_t	 vector3d_cartesian::get_X() const
{
	return this->coordinates[0];
}

int32_t	 vector3d_cartesian::get_Y() const
{
	return this->coordinates[1];
}

int32_t	 vector3d_cartesian::get_Z() const
{
	return this->coordinates[2];
}

const vector<int32_t>& vector3d_cartesian::get_vector() const
{
	return this->coordinates;
}

opcode	 vector3d_cartesian::set_X(int32_t val)
{
	this->coordinates[0] = val;
	compute_magnitude();
	return STATUS_OK;
}

opcode	 vector3d_cartesian::set_Y(int32_t val)
{
	this->coordinates[1] = val;
	compute_magnitude();
	return STATUS_OK;
}

opcode	 vector3d_cartesian::set_Z(int32_t val)
{
	this->coordinates[2] = val;
	compute_magnitude();
	return STATUS_OK;
}

opcode vector3d_cartesian::normalise()
{
	//normalisation leads to floating point vector sizes... need to remake all vector engine
	return STATUS_OK;
}

double vector3d_cartesian::get_magnitude() const
{
	
	return compute_magnitude();
}

vector3d_cartesian::vector3d_cartesian() :
	coordinates(3,0),
	_magnitude(0)
{}

vector3d_cartesian::vector3d_cartesian(int32_t x, int32_t y, int32_t z) :
	coordinates({x,y,z}),
	_magnitude(0)
{
	compute_magnitude();
}

vector3d_cartesian::~vector3d_cartesian()
{

}

const vector3d_cartesian& vector3d_cartesian::operator*=(int32_t factor)
{
	this->coordinates[0] *= factor;
	this->coordinates[1] *= factor;
	this->coordinates[2] *= factor;
	return *this;
}

const vector3d_cartesian& vector3d_cartesian::operator+=(const vector3d_cartesian& other)
{
	this->coordinates[0] += other.get_X();
	this->coordinates[1] += other.get_Y();
	this->coordinates[2] += other.get_Z();
	return *this;
}

const vector3d_cartesian& vector3d_cartesian::operator-=(const vector3d_cartesian& other)
{
	this->coordinates[0] -= other.get_X();
	this->coordinates[1] -= other.get_Y();
	this->coordinates[2] -= other.get_Z();
	return *this;

}


const vector3d_cartesian operator*(int32_t factor, const vector3d_cartesian& other)
{
	vector3d_cartesian res_vector(other);
	res_vector *= factor;
	return res_vector;
}
const vector3d_cartesian operator*(const vector3d_cartesian& other, int32_t factor)
{
	return factor * other;
}
const int32_t operator*(const vector3d_cartesian& v1, const vector3d_cartesian& v2)
{
	return v1.get_X() * v2.get_X() + 
			v1.get_Y() * v2.get_Y() + 
			v1.get_Z() * v2.get_Z();
}

//cross product
const vector3d_cartesian operator^(const vector3d_cartesian& v1, const vector3d_cartesian& v2)
{
	vector3d_cartesian new_vect(
			v1.get_Y()*v2.get_Z() - v1.get_Z() * v2.get_Y(),
			v1.get_Z()*v2.get_X() - v1.get_X() * v2.get_Z(),
			v1.get_X()*v2.get_Y() - v1.get_Y() * v2.get_X()
		);
	return new_vect;
}

const vector3d_cartesian operator+(const vector3d_cartesian& v1, const vector3d_cartesian& v2)
{
	vector3d_cartesian res_vector(v1);
	res_vector += v2;
	return res_vector;
}
const vector3d_cartesian operator-(const vector3d_cartesian& v1, const vector3d_cartesian& v2)
{
	vector3d_cartesian res_vector(v1);
	res_vector -= v2;
	return res_vector;
}

const bool operator==(const vector3d_cartesian& v1, const vector3d_cartesian& v2)
{
	if(v1.get_X() == v2.get_X() && v1.get_Y()==v2.get_Y() && v1.get_Z() == v2.get_Z()){
		return true;
	}
	return false;
}

double get_angle(const vector3d_cartesian& v1, const vector3d_cartesian& v2)
{
	assert(v1.get_magnitude() > 0 && v2.get_magnitude() > 0);
	return v1*v2 / (v1.get_magnitude() * v2.get_magnitude()); 
}

}