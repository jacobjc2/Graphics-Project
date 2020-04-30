/*
* File: image.h
* Author: Jacob Christensen
* Course: CS3210
* Date: 04/07/19
*/

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "x11context.h"
#include "shape.h"
#include "viewcontext.h"
#include <vector>
#include <string>

class image {
	//Container for the shapes to be held
	std::vector<shape *> shapes;

public:
	// Constructor - create an empty image object
	image();

	// Copy constructor
	image(const image& from);

	// Destructor - free allocated memory
	~image();

	// Copy Constructor - performs deep copy from rhs to this
	image& operator=(const image& rhs);

	void add(shape* s);

	// Draw - interates throught the vector, drawing all of
	//        the shapes
	void draw(GraphicsContext* gc, ViewContext& vc) const;

	// Erase - clears all the shapes from the shapes vector
	void erase(image& img);

	// Out - this method will send the properties of the image
	// 		 to the output stream
	virtual std::ostream& out(std::ostream& os) const;

	// In - takes in the image properties from a text file
	virtual std::istream& in(std::istream& in);

	std::vector<shape *>& getShapes();
};

// Global Stream Operators
std::ostream& operator<<(std::ostream& os, const image& rhs);

std::istream& operator>>(std::istream& is, image& rhs);

#endif