/*
* File: viewcontext.h
* Author: Jacob Christensen
* Course: CS3210
* Date: 04/25/19
*/

#ifndef _VIEW_CONTEXT_
#define _VIEW_CONTEXT_

#include "matrix.h"
#include "gcontext.h"


class ViewContext {
private:
	matrix transformation;
	matrix inverse;
	matrix* viewPoint;
	matrix* refPoint;
	matrix* normal;
	matrix* L;
	matrix* M;
	matrix* V;
	matrix* unit_L;
	matrix* unit_M;
	matrix* unit_N;
	double ro_angle, trans_vert, trans_hor, scale_factor, focus_distance;

public:
	// Constructor
	ViewContext();
	// Destructor
	~ViewContext();
	// Convert coordinates from model to device
	matrix modelToDevice(matrix model_coor, GraphicsContext* gc) const;
	// Convert coordinates from device to model
	matrix deviceToModel(matrix device_coor, GraphicsContext* gc) const;
	// Convert coordinates from model to view
	matrix modelToView(matrix model_coor) const;
	// Convert coordinates from view to projection
	matrix viewToProjection(matrix view_coor) const;


	// Method to add a scaling transform to the compound transformation
	void scale(const double factor);

	// Method to add a rotation to the compound transformation
	void rotate_H(const double angle);

	// Method to add a rotation to the compound transformation
	void rotate_V(const double angle);

	// Method to add a translation to the compound transformation
	void translate(const double horizontal, const double vertical);

	// Method to set the focus distance for point projection
	void setFocus(const double distance);

	// Applies the compound transformation to the provided matrix
	matrix transform(matrix mat) const;
	// Applies the inverse compound transformation to the provided matrix
	matrix invert(matrix mat) const;

	// Resets the transformation and the viewport
	void reset(GraphicsContext* gc);
};

#endif