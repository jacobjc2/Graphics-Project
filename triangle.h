/*
* File: triangle.h
* Author: Jacob Christensen
* Course: CS3210
* Date: 03/29/19
*/

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_


#include "shape.h"
#include "x11context.h"
#include "viewcontext.h"
#include "matrix.h"

class triangle : public shape {
	matrix p1;
	matrix p2;

public:

	//	Constructor - calls shape constructor
	triangle(unsigned int color, matrix p0, matrix p1, matrix p2);
	// Copy Constructor - creates a new triangle that is a 
	//      			  deep copy of from
	triangle(const triangle& from);

	// Accessor for P1
	matrix get_p1() const;
	// Accessor for P2
	matrix get_p2() const;

	// Destructor
	~triangle();

	// Clone - returns a new triangle that is a deep copy of this
	shape* clone() const;

	// Assignment Operator - performs a deep copy from rhs to this
	triangle& operator=(const triangle& rhs);

	//Draw - draws line segments between each vertex
	void draw(GraphicsContext* gc, ViewContext& vc) const;

	// Out - this method will send the properties of the shape
	// 		 to the output stream
	std::ostream& out(std::ostream& os) const;

	// In - takes in the shape properties from a text file
	std::istream& in(std::istream& in);
};

// Global Stream Operators
std::ostream& operator<<(std::ostream& os, const triangle& rhs);

std::istream& operator>>(std::istream& is, triangle& rhs);


#endif