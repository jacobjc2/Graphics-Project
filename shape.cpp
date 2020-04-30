/*
* File: shape.cpp
* Author: Jacob Christensen
* Course: CS3210
* Date: 03/28/19
*/

#include "shape.h"

#include <string>
#include <iomanip>
#include <iostream>

// Constructor for initializing Shape object
shape::shape(unsigned int color, matrix p0):color(color),p0(p0){}

// Copy constructor
shape::shape(const shape& from):color(from.color),p0(from.p0){}

// Destructor - free allocated memory
shape::~shape() {}

// Color accessor
unsigned int shape::get_color() const {
	return color;
}

// p0 accessor
matrix shape::get_p0() const {
	return p0;
}

// Copy Constructor - performs deep copy from rhs to this
shape& shape::operator=(const shape& rhs) {
	if(this != &rhs) {
		p0 = rhs.p0;
		color = rhs.color;
	}
	return *this;
}

// Out - this method will send the properties of the shape
// 		 to the output stream
std::ostream& shape::out(std::ostream& os) const{
	os << "C\n" << std::to_string(get_color()) << "\n";
	os << "P0 \n" << (get_p0())[0][0] << std::endl;
	os << (get_p0())[1][0] << std::endl;
	os << (get_p0())[2][0] << std::endl;
	return os;
}

// In - takes in the shape properties from a text file
std::istream& shape::in(std::istream& in) {
	std::string identifier, point_0_str;
	double x, y, z;
	matrix* new_p0 = new matrix(4,1);
	in >> identifier;
	getline(in,point_0_str);
	if(identifier == "vertex") {
		std::stringstream(point_0_str) >> x >> y >> z;
		(*new_p0)[0][0] = x;
		(*new_p0)[1][0] = y;
		(*new_p0)[2][0] = z;
		// Set the last matrix entry to 1.0
		(*new_p0)[3][0] = 1;
		p0 = *new_p0;
	}
	delete new_p0;
	return in;
}

// Stream Insertion Operator - Calls out function
std::ostream& operator<<(std::ostream& os, const shape& rhs) {
	rhs.out(os);
	return os;
}
