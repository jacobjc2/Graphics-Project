/*
* File: line.cpp
* Author: Jacob Christensen
* Course: CS3210
* Date: 03/29/19
*/
#include "line.h"
#include "x11context.h"
#include "viewcontext.h"
#include <sstream>

line::line(unsigned int color, matrix p0, matrix p1):shape(color,p0),p1(p1){}

line::line(const line& from):line(from.get_color(), from.get_p0(), from.get_p1()){}

line::~line(){}

matrix line::get_p1() const {
	return p1;
}

// Clone
shape* line::clone() const {
	return new line(*this);
}

line& line::operator=(const line& rhs) {
	if(this != &rhs) {
		shape::operator=(rhs);
		this->p1 = rhs.get_p1();
	}
	return *this;
}

//Draw
void line::draw(GraphicsContext* gc, ViewContext& vc) const{
	matrix disp_p0 = this->get_p0();
	disp_p0 = vc.modelToView(disp_p0);
	disp_p0 = vc.viewToProjection(disp_p0);
	disp_p0 = disp_p0 * (1.0/disp_p0[3][0]);
	disp_p0 = vc.modelToDevice(disp_p0, gc);
	disp_p0 = vc.transform(disp_p0);

	matrix disp_p1 = this->get_p1();
	disp_p1 = vc.modelToView(disp_p1);
	disp_p1 = vc.viewToProjection(disp_p1);
	disp_p1[3][0] = disp_p1[3][0] * (1.0/disp_p1[3][0]);
	disp_p1 = vc.modelToDevice(disp_p1, gc);
	disp_p1 = vc.transform(disp_p1);
	gc->setColor(this->get_color());
	gc->drawLine(disp_p0[0][0],disp_p0[1][0],disp_p1[0][0],disp_p1[1][0]);
}

//Output
std::ostream& line::out(std::ostream& os) const{
	os << "L" << std::endl;
	this->shape::out(os);
	os << "P1 \n" << (get_p1())[0][0] << std::endl;
	os << (get_p1())[1][0] << std::endl;
	os << (get_p1())[2][0] << std::endl;
	os << "END" << std::endl;
	return os;
}

std::istream& line::in(std::istream& in) {
	this->shape::in(in);
	std::string identifier, point_1_str;
	matrix* new_p1 = new matrix(4,1);
	getline(in,point_1_str); 
	std::stringstream(point_1_str) >> *new_p1[0][0];
	getline(in,point_1_str);
	std::stringstream(point_1_str) >> *new_p1[0][1];
	getline(in,point_1_str);
	std::stringstream(point_1_str) >> *new_p1[0][2];
	getline(in,point_1_str);
	p1 = *new_p1;
	delete new_p1;
	return in;
}

std::ostream& operator<<(std::ostream& os, const line& rhs) {
	rhs.out(os);
	return os;
}

std::istream& operator>>(std::istream& is, line& rhs) {
	rhs.in(is);
	return is;
}