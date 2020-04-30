/*
* File: image.cpp
* Author: Jacob Christensen
* Course: CS3210
* Date: 04/07/19
*/

#include "x11context.h"
#include "image.h"
#include "matrix.h"
#include "shape.h"
#include "line.h"
#include "triangle.h"
#include <vector>
#include <string>
#include <iostream>

// Constructor - create an image object 
image::image() {}


// Copy constructor
image::image(const image& from) {
	for(auto i = from.shapes.begin(); i != from.shapes.end(); i++) {
		shapes.push_back((*i)->clone());
	}
}

// Destructor - free allocated memory
image::~image() {
	for(auto i = shapes.begin(); i != shapes.end(); i++) {
		delete *i;
	}
}

// Assignment operator- performs deep copy from rhs to this
image& image::operator=(const image& rhs) {
	if(this != &rhs) {
		// Delete current image
		for(auto i = shapes.begin(); i != shapes.end(); i++) {
			delete *i;
		}
		// Copy shapes
		for(auto i = rhs.shapes.begin(); i != rhs.shapes.end(); i++) {
			shapes.push_back((*i)->clone());
		}
	}

	return *this;
}

// Add - add a new shape to the image
void image::add(shape* s) {
	shapes.push_back(s);
}

// Draw - draws the image. Pure virtual, functionality is
// 		  defined in subclasses
void image::draw(GraphicsContext* gc, ViewContext& vc) const {
	if(shapes.size() > 0) {
		for(auto i = shapes.begin(); i != shapes.end(); i++) {
			(*i)->draw(gc, vc);
		}
	}
}

// Erase - Clear the shapes from an image
void image::erase(image& img) {
	if(shapes.size() > 0) {
		for(auto i = img.shapes.begin(); i != img.shapes.end(); i++) {
			delete *i;
		}
		shapes.clear();
	}
}

// Out - this method will send the properties of the image
// 		 to the output stream
std::ostream& image::out(std::ostream& os) const {
	if(shapes.size() > 0) {
		for(auto i = shapes.begin(); i != shapes.end(); i++) {
			os << *(*i) << std::endl;
		}
	}
	return os;
}

// In - takes in the image properties from a text file
std::istream& image::in(std::istream& in) {
	std::string identifier, in_line;
	bool inFacet = false;
	matrix p0(4,1);
	matrix p1(4,1);
	matrix p2(4,1);
	p0[3][0] = 1.0;
	p1[3][0] = 1.0;
	p2[3][0] = 1.0;
	int next_c = in.peek();
	while(next_c != EOF) {
		in >> identifier;
		getline(in,in_line);
		// Identifying the start of a new facet in the file
		if(identifier == "facet" && !inFacet) {
			inFacet = true;
		}

		if(identifier == "outer" && inFacet) {
			triangle* t = new triangle(0x00FF00, p0, p1, p2);
			in >> *t;
			shapes.push_back(t);
		}
		
		// Identifying the end of a facet
		if(identifier == "endfacet" && inFacet) {
			inFacet = false;
		}
		next_c = in.peek();
	}
	return in;
}

std::vector<shape *>& image::getShapes() {
	return shapes;
}

// Stream insertion operator - not a member function
std::ostream& operator<<(std::ostream& os, const image& rhs) {
	rhs.out(os);
	return os;
}

// Stream Extraction operator - not a member function
std::istream& operator>>(std::istream& is, image& rhs) {
	rhs.in(is);
	return is;
}
