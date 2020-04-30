/*
* File: line.h
* Author: Jacob Christensen
* Course: CS3210
* Date: 03/29/19
*/

#ifndef _LINE_H_
#define _LINE_H_


#include "shape.h"
#include "x11context.h"
#include "viewcontext.h"
#include "matrix.h"

class line : public shape {
	matrix p1;

public:

	//	Constructor - calls shape constructor
	line(unsigned int color, matrix p0, matrix p1);

	// Copy Constructor - Creates new line that is a deep copy
	//  				  of from
	line(const line& from);

	// Accessor for P1
	matrix get_p1() const;

	// Destructor
	~line();

	// Clone - returns a new point that is a deep copy of this
	virtual shape* clone() const;

	// Assignment Operator - performs a deep copy from rhs to this
	line& operator=(const line& rhs);

	//Draw - Draws a line segment between P0 and P1
	void draw(GraphicsContext* gc, ViewContext& vc) const;

	// Out - this method will send the properties of the shape
	// 		 to the output stream
	std::ostream& out(std::ostream& os) const;
	// In - takes in the shape properties from a text file
	std::istream& in(std::istream& in);
};

// Global Stream Operators
std::ostream& operator<<(std::ostream& os, const line& rhs);

std::istream& operator>>(std::istream& is, line& rhs);

#endif