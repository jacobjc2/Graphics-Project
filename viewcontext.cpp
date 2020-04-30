/*
* File: viewcontext.cpp
* Author: Jacob Christensen
* Course: CS3210
* Date: 04/28/19
*/

#include "viewcontext.h"
#include "matrix.h"
#include "gcontext.h"
#include "image.h"
#include "line.h"
#include "triangle.h"

#include <cmath>
#include <iostream>

using namespace std;

ViewContext::ViewContext():transformation(matrix::identity(4)),inverse(matrix::identity(4)),
viewPoint(new matrix(4,1)), refPoint(new matrix(4,1)),normal(new matrix(3,1)),L(new matrix(3,1)),
M(new matrix(3,1)), V(new matrix(3,1)), unit_L(new matrix(3,1)),unit_M(new matrix(3,1)),unit_N(new matrix(3,1)) {
	ro_angle = trans_vert = trans_hor = scale_factor = 0.0;
	focus_distance = 100.0;
	(*V)[1][0] = 1;
	(*viewPoint)[0][0] = 2;
	(*viewPoint)[1][0] = 2;
	(*viewPoint)[2][0] = 5;
	(*viewPoint)[3][0] = 1.0;
	(*refPoint)[0][0] =  0;
	(*refPoint)[1][0] = 0;
	(*refPoint)[2][0] = 0;
	(*refPoint)[3][0] = 0;
	(*normal)[0][0] = (*viewPoint)[0][0] - (*refPoint)[0][0];
	(*normal)[1][0] = (*viewPoint)[1][0] - (*refPoint)[1][0];
	(*normal)[2][0] = (*viewPoint)[2][0] - (*refPoint)[2][0];
	(*L) = matrix::crossProduct(*V, *normal);
	(*M) = matrix::crossProduct(*normal, *L);
	(*unit_L) = (*L) * (1.0/sqrt((pow((*L)[0][0],2) + pow((*L)[1][0],2) + pow((*L)[2][0],2))));
	(*unit_M) = (*M) * (1.0/sqrt((pow((*M)[0][0],2) + pow((*M)[1][0],2) + pow((*M)[2][0],2))));
	(*unit_N) = (*normal) * (1.0/sqrt((pow((*normal)[0][0],2) + pow((*normal)[1][0],2) + pow((*normal)[2][0],2))));
}

ViewContext::~ViewContext() {
	delete viewPoint;
	delete refPoint;
	delete normal;
	delete M;
	delete L;
	delete V;
	delete unit_L;
	delete unit_M;
	delete unit_N;
}

matrix ViewContext::modelToDevice(matrix model_coor, GraphicsContext* gc) const {
	matrix ret_mat(4,1);
	matrix reflect = matrix::identity(4);
	matrix trans = matrix::identity(4);
	reflect[1][1] = -1;
	trans[1][3] = (gc->getWindowHeight());
	// Reflect the model coordinates over the x-axis
	ret_mat = reflect * model_coor;
	// Shift the coordinates down by the height of the viewport
	ret_mat = trans * ret_mat;
	return ret_mat;
}

matrix ViewContext::deviceToModel(matrix device_coor, GraphicsContext* gc) const {
	matrix ret_mat(4,1);
	matrix reflect = matrix::identity(4);
	matrix trans = matrix::identity(4);
	reflect[1][1] = -1;
	trans[1][3] = -(gc->getWindowHeight());
	// Shift the coordinates up by the height of the viewport
	ret_mat = trans * device_coor;
	// Reflect the coordinates over the x-axis
	ret_mat = reflect * ret_mat;
	return ret_mat;
}

matrix ViewContext::modelToView(matrix model_coor) const {
	matrix retVal(4,1);
	matrix mTv = matrix::identity(4);
	mTv[0][0] = (*unit_L)[0][0];
	mTv[0][1] = (*unit_L)[1][0];
	mTv[0][2] = (*unit_L)[2][0];
	mTv[0][3] = -(((*unit_L)[0][0] * (*viewPoint)[0][0]) + ((*unit_L)[1][0] * (*viewPoint)[1][0]) + ((*unit_L)[2][0] * (*viewPoint)[2][0]));
	mTv[1][0] = (*unit_M)[0][0];
	mTv[1][1] = (*unit_M)[1][0];
	mTv[1][2] = (*unit_M)[2][0];
	mTv[1][3] = -(((*unit_M)[0][0] * (*viewPoint)[0][0]) + ((*unit_M)[1][0] * (*viewPoint)[1][0]) + ((*unit_M)[2][0] * (*viewPoint)[2][0]));
	mTv[2][0] = (*unit_N)[0][0];
	mTv[2][1] = (*unit_N)[1][0];
	mTv[2][2] = (*unit_N)[2][0];
	mTv[2][3] = -(((*unit_N)[0][0] * (*viewPoint)[0][0]) + ((*unit_N)[1][0] * (*viewPoint)[1][0]) + ((*unit_N)[2][0] * (*viewPoint)[2][0]));
	retVal = mTv *  model_coor;
	return retVal;
}

matrix ViewContext::viewToProjection(matrix view_coor) const {
	matrix retVal(4,1);
	matrix vTp = matrix::identity(4);
	vTp[2][2] = 0;
	vTp[3][2] = -1.0/focus_distance;
	retVal = vTp * view_coor;
	return retVal;
}


void ViewContext::scale(double factor) {
	scale_factor *= factor;
	// Create the transform
	matrix scale_mat = matrix::identity(4);
	matrix i_scale_mat = matrix::identity(4);
	scale_mat[0][0] = scale_mat[1][1] = scale_mat[2][2] = factor;
	i_scale_mat[0][0] = i_scale_mat[1][1] = i_scale_mat[2][2] = 1/factor;
	// Add the transform to the compound 
	this->translate(-400,-300);
	transformation = scale_mat * transformation;
	this->translate(400,300);
	this->translate(0,600);
	inverse = i_scale_mat * inverse;
	this->translate(0,-600);
	return;
}

void ViewContext::rotate_H(double angle) {
	ro_angle += angle;
	// Create the rotation transform
	matrix ro = matrix::identity(4);
	matrix i_ro = matrix::identity(4);
	ro[0][0] = cos(angle * 3 / 180);
	ro[0][2] = sin(angle * 3 / 180);
	ro[2][0] = -(sin(angle * 3 / 180));
	ro[2][2] = cos(angle * 3 / 180);
	i_ro[0][0] = cos(-angle * 3 / 180);
	i_ro[0][1] = -(sin(-angle * 3 / 180));
	i_ro[1][0] = sin(-angle * 3 / 180);
	i_ro[1][1] = cos(-angle * 3 / 180);
	// Add the rotation to the viewpoint
	(*viewPoint) = ro * (*viewPoint);
	(*normal)[0][0] = (*viewPoint)[0][0] - (*refPoint)[0][0];
	(*normal)[1][0] = (*viewPoint)[1][0] - (*refPoint)[1][0];
	(*normal)[2][0] = (*viewPoint)[2][0] - (*refPoint)[2][0];
	(*L) = matrix::crossProduct(*V, *normal);
	(*M) = matrix::crossProduct(*normal, *L);
	(*unit_L) = (*L) * (1.0/sqrt((pow((*L)[0][0],2) + pow((*L)[1][0],2) + pow((*L)[2][0],2))));
	(*unit_M) = (*M) * (1.0/sqrt((pow((*M)[0][0],2) + pow((*M)[1][0],2) + pow((*M)[2][0],2))));
	(*unit_N) = (*normal) * (1.0/sqrt((pow((*normal)[0][0],2) + pow((*normal)[1][0],2) + pow((*normal)[2][0],2))));
	return;
}

void ViewContext::rotate_V(double angle) {
	ro_angle += angle;
	// Create the rotation transform
	matrix ro_z = matrix::identity(4);
	matrix ro_y = matrix::identity(4);
	matrix ro_vector = matrix(3,1);
	matrix z_vector = matrix(3,1);
	z_vector[2][0] = 1.0;
	ro_vector[0][0] = (*unit_L)[0][0];
	ro_vector[2][0] = (*unit_L)[2][0];
	double xy_angle = matrix::vectorAngle(z_vector,ro_vector);
	// Rotate around y-axis
	this->rotate_H(-xy_angle * (180 / 3));
	ro_z[0][0] = cos(angle * 3 / 180);
	ro_z[1][0] = sin(angle * 3 / 180);
	ro_z[0][1] = -(sin(angle * 3 / 180));
	ro_z[1][1] = cos(angle * 3 / 180);
	// Add the rotation to the viewpoint
	(*viewPoint) = ro_z * (*viewPoint);
	(*normal)[0][0] = (*viewPoint)[0][0] - (*refPoint)[0][0];
	(*normal)[1][0] = (*viewPoint)[1][0] - (*refPoint)[1][0];
	(*normal)[2][0] = (*viewPoint)[2][0] - (*refPoint)[2][0];
	(*L) = matrix::crossProduct(*V, *normal);
	(*M) = matrix::crossProduct(*normal, *L);
	(*unit_L) = (*L) * (1.0/sqrt((pow((*L)[0][0],2) + pow((*L)[1][0],2) + pow((*L)[2][0],2))));
	(*unit_M) = (*M) * (1.0/sqrt((pow((*M)[0][0],2) + pow((*M)[1][0],2) + pow((*M)[2][0],2))));
	(*unit_N) = (*normal) * (1.0/sqrt((pow((*normal)[0][0],2) + pow((*normal)[1][0],2) + pow((*normal)[2][0],2))));
	// Rotate back around the y-axis
	this->rotate_H(xy_angle * (180 / 3));
	return;
}

void ViewContext::translate(double horizontal, double vertical) {
	// Create the translation transform
	matrix trans = matrix::identity(4);
	matrix i_trans = matrix::identity(4);
	trans[0][3] += horizontal;
	trans[1][3] += vertical;
	i_trans[0][3] -= horizontal;
	i_trans[1][3] -= vertical;
	// Apply the transform to the compound
	transformation = trans * transformation;
	inverse = i_trans * inverse;
	return;
}

void ViewContext::setFocus(const double distance) {
	focus_distance = distance;
}

// Apply the transformation to the given matrix
matrix ViewContext::transform(matrix mat) const {
	return transformation * mat;
} 

// Apply the inverse transformation to the given matrix
matrix ViewContext::invert(matrix mat) const {
	return inverse * mat;
} 

void ViewContext::reset(GraphicsContext* gc) {
	gc->clear();
	transformation = matrix::identity(4);
	inverse = matrix::identity(4);
	focus_distance = 100.0;
	(*V)[1][0] = 1;
	(*viewPoint)[0][0] = 2;
	(*viewPoint)[1][0] = 2;
	(*viewPoint)[2][0] = 5;
	(*viewPoint)[3][0] = 1.0;
	(*refPoint)[0][0] =  0;
	(*refPoint)[1][0] = 0;
	(*refPoint)[2][0] = 0;
	(*refPoint)[3][0] = 0;
	(*normal)[0][0] = (*viewPoint)[0][0] - (*refPoint)[0][0];
	(*normal)[1][0] = (*viewPoint)[1][0] - (*refPoint)[1][0];
	(*normal)[2][0] = (*viewPoint)[2][0] - (*refPoint)[2][0];
	(*L) = matrix::crossProduct(*V, *normal);
	(*M) = matrix::crossProduct(*normal, *L);
	(*unit_L) = (*L) * (1.0/sqrt((pow((*L)[0][0],2) + pow((*L)[1][0],2) + pow((*L)[2][0],2))));
	(*unit_M) = (*M) * (1.0/sqrt((pow((*M)[0][0],2) + pow((*M)[1][0],2) + pow((*M)[2][0],2))));
	(*unit_N) = (*normal) * (1.0/sqrt((pow((*normal)[0][0],2) + pow((*normal)[1][0],2) + pow((*normal)[2][0],2))));
}
