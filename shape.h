/*
* File: shape.h
* Author: Jacob Christensen
* Course: CS3210
* Date: 03/27/19
*/

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "matrix.h"
#include "x11context.h"
#include "viewcontext.h"
#include <iostream>
#include <string>

class shape {
	// Int value that describes the color
	unsigned int color;
	// Matrix to hold the origin point
	matrix p0;

protected:
	// Copy Constructor - performs deep copy from rhs to this
	// 					  only to be accessed by children of shape
	shape& operator=(const shape& rhs);

public:
	// Constructor - create a shape object with user specified
	// 				 RGB value and center point at p0 (x,y,z,1.0)
	shape(unsigned int color, matrix p0);

	// Copy constructor
	shape(const shape& from);

	// Destructor - free allocated memory
	virtual ~shape();

	// Accessors for the private properties
	unsigned int get_color() const;
	matrix get_p0() const;

	// Clone - makes copies of shapes (Pure Virtual)
	virtual shape* clone() const = 0;

	// Draw - draws the shape. Pure virtual, functionality is
	// 		  defined in subclasses
	//TODO
	virtual void draw(GraphicsContext* gc, ViewContext& vc) const = 0;

	// Out - this method will send the properties of the shape
	// 		 to the output stream
	virtual std::ostream& out(std::ostream& os) const;

	// In - takes in the shape properties from a text file
	virtual std::istream& in(std::istream& in);
};

// Global Stream Operators
std::ostream& operator<<(std::ostream& os, const shape& rhs);

std::istream& operator>>(std::istream& is, shape& rhs);

#endif