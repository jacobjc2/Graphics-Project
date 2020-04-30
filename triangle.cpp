/*
* File: triangle.cpp
* Author: Jacob Christensen
* Course: CS3210
* Date: 03/29/19
*/
#include "triangle.h"
#include "x11context.h"
#include "viewcontext.h"
#include <sstream>
#include <iostream>

// Constructor for initializing triangle objects
triangle::triangle(unsigned int color, matrix p0, matrix p1, matrix p2):shape(color,p0),p1(p1),p2(p2){}

// Copy Constructor
triangle::triangle(const triangle& from):triangle(from.get_color(), from.get_p0(), from.get_p1(), from.get_p2()){}

// Destructor - nothing new needs to happen
triangle::~triangle(){}

// Accessor for P1
matrix triangle::get_p1() const {
	return p1;
}

// Accesssor for P2
matrix triangle::get_p2() const {
	return p2;
}

// Assignment operator - performs deep copy from rhs to this
triangle& triangle::operator=(const triangle& rhs) {
	if(this != &rhs) {
		shape::operator=(rhs);
		this->p1 = rhs.get_p1();
		this->p2 = rhs.get_p2();
	}
	return *this;
}

// Clone - returns a deep copy of the triangle
shape* triangle::clone() const {
	return new triangle(*this);
}

//Draw - draw lines between each vertex
void triangle::draw(GraphicsContext* gc, ViewContext& vc) const{
	matrix disp_p0 = this->get_p0();
	disp_p0 = vc.modelToView(disp_p0);
	disp_p0 = vc.viewToProjection(disp_p0);
	disp_p0 = vc.modelToDevice(disp_p0, gc);
	disp_p0 = disp_p0 * (1.0/disp_p0[3][0]);
	disp_p0 = vc.transform(disp_p0);
	matrix disp_p1 = this->get_p1();
	disp_p1 = vc.modelToView(disp_p1);
	disp_p1 = vc.viewToProjection(disp_p1);
	disp_p1 = vc.modelToDevice(disp_p1, gc);
	disp_p1 = disp_p1 * (1.0/disp_p1[3][0]);
	disp_p1 = vc.transform(disp_p1);
	matrix disp_p2 = this->get_p2();
	disp_p2 = vc.modelToView(disp_p2);
	disp_p2 = vc.viewToProjection(disp_p2);
	disp_p2 = vc.modelToDevice(disp_p2, gc);
	disp_p2 = disp_p2 * (1.0/disp_p2[3][0]);
	disp_p2 = vc.transform(disp_p2);
	//std::cout << disp_p0 << std::endl;
	//std::cout << disp_p1 << std::endl;
	//std::cout << disp_p2 << std::endl;
	gc->setColor(this->get_color());
	gc->drawLine(disp_p0[0][0],disp_p0[1][0],disp_p1[0][0],disp_p1[1][0]);
	gc->drawLine(disp_p1[0][0],disp_p1[1][0],disp_p2[0][0],disp_p2[1][0]);
	gc->drawLine(disp_p2[0][0],disp_p2[1][0],disp_p0[0][0],disp_p0[1][0]);
}

//Output - output properties to ostream
std::ostream& triangle::out(std::ostream& os) const{
	os << "T" << std::endl;
	this->shape::out(os);
	os << "P1 \n" << (get_p1())[0][0] << std::endl;
	os << (get_p1())[1][0] << std::endl;
	os << (get_p1())[2][0] << std::endl;
	os << "P2 \n" << (get_p2())[0][0] << std::endl;
	os << (get_p2())[1][0] << std::endl;
	os << (get_p2())[2][0] << std::endl;
	os << "END" << std::endl;
	return os;
}

//Input -take in properties from istream
std::istream& triangle::in(std::istream& in) {
	unsigned int vector_count = 0;
	double x, y, z;
	std::string identifier, point_str;
	matrix* new_p1 = new matrix(4,1);
	matrix* new_p2 = new matrix(4,1);
	this->shape::in(in);
	vector_count++;
	in >> identifier;
	getline(in,point_str);
	while(identifier != "endloop" && vector_count < 3) {
		if(identifier == "vertex" && vector_count == 1) {
			std::stringstream(point_str) >> x >> y >> z;
			(*new_p1)[0][0] = x;
			(*new_p1)[1][0] = y;
			(*new_p1)[2][0] = z;
			// Set the last matrix entry to 1.0
			(*new_p1)[3][0] = 1;
			p1 = *new_p1;
			vector_count++;
		}
		else if(identifier == "vertex" && vector_count == 2) {
			std::stringstream(point_str) >> x >> y >> z;
			(*new_p2)[0][0] = x;
			(*new_p2)[1][0] = y;
			(*new_p2)[2][0] = z;
			// Set the last matrix entry to 1.0
			(*new_p2)[3][0] = 1;
			p2 = *new_p2;
			vector_count++;
		}
		in >> identifier;
		getline(in,point_str);
	}
	delete new_p1;
	delete new_p2;
	return in;
}

// Global Stream Operators
std::ostream& operator<<(std::ostream& os, const triangle& rhs) {
	rhs.out(os);
	return os;
}

std::istream& operator>>(std::istream& is, triangle& rhs) {
	rhs.in(is);
	return is;
}