/*
* File: matrix.cpp
* Author: Jacob Christensen
* Course: CS3210
* Date: 03/14/19
*/

#include "matrix.h"
#include <string>
#include <cmath>
#include <iostream>
 
using namespace std;

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	}
	else 
	{
		the_matrix = new double *[rows];
		for(unsigned int i=0;i<rows;i++) 
		{
			the_matrix[i] = new double[cols];
		}
		//Clearing all existing values in the memory
		for(unsigned int r=0;r<rows;r++) 
		{
			for(unsigned int c=0;c<cols;c++) 
			{
				the_matrix[r][c] = 0.0;
			}
		}
	}
}

// Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	the_matrix = new double *[rows];
	for(unsigned int x=0;x<rows;x++) 
	{
		the_matrix[x] = new double[cols];
		for(unsigned int y=0;y<cols;y++) {
			the_matrix[x][y] = from.the_matrix[x][y];
		}
	}
}

// Destructor
matrix::~matrix()
{
	for(unsigned int i=0;i<rows;i++) {
		delete [] the_matrix[i];
	}
	delete [] the_matrix;
	rows = 0;
	cols = 0;
}

matrix matrix::crossProduct(matrix a, matrix b) {
	if(a.rows == 3 && a.cols == 1 && b.rows == 3 && b.cols == 1) {
		matrix retVal(3,1);
		retVal[0][0] = (a[1][0] * b[2][0]) - (a[2][0] * b[1][0]);
		retVal[1][0] = (a[2][0] * b[0][0]) - (a[0][0] * b[2][0]);
		retVal[2][0] = (a[0][0] * b[1][0]) - (a[1][0] * b[0][0]);
		return retVal;
	}
	else {
		throw matrixException(
			"Cross product must be between two 3x1 matrices");
	}
	
}

double matrix::vectorAngle(const matrix a, const matrix b) {
	double mag_a = sqrt((pow(a[0][0],2) + pow(a[1][0],2) + pow(a[2][0],2)));
	double mag_b = sqrt((pow(b[0][0],2) + pow(b[1][0],2) + pow(b[2][0],2)));
	double dot_prod = (a[0][0] * b[0][0]) + (a[1][0] * b[1][0]) + (a[2][0] * b[2][0]);
	return acos(dot_prod/(mag_a * mag_b));
}


// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{
	// check for self-assignment
	if(this != &rhs) 
	{
		for(unsigned int i=0;i<rows;i++) {
			delete [] the_matrix[i];
		}
		delete [] the_matrix;

		rows = rhs.rows;
		cols = rhs.cols;
		the_matrix = new double *[rows];
		for(unsigned int x=0;x<rows;x++) 
		{
			the_matrix[x] = new double[cols];
			for(unsigned int y=0;y<cols;y++) 
			{
				the_matrix[x][y] = rhs.the_matrix[x][y];
			}
		}
	}
	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	if(size < 1) {
		throw matrixException(
			"Cannot have an identity matrix with size < 0");
	}
	// use p-constructor
	matrix ident(size, size);
	for(unsigned int x=0;x<size;x++) 
	{
		for(unsigned int y=0;y<size;y++) 
		{
			if(x == y)
			{
				ident.the_matrix[x][y] = 1;
			}
			else 
			{
				ident.the_matrix[x][y] = 0;
			}
		}
	}
	return ident;
}


// Binary operations
matrix matrix::operator+(const matrix& rhs) const
{
	matrix retVal(rows, cols);
	if(rows != rhs.rows || cols != rhs.cols) 
	{
		throw matrixException("Matrices cannot be added: Different sizes");
	}
	else {
		for(unsigned int r=0;r<rows;r++) {
			for(unsigned int c=0;c<cols;c++) {
				retVal[r][c] = the_matrix[r][c] + rhs[r][c];
			}
		}
	}
	return retVal;
}


matrix matrix::operator*(const matrix& rhs) const
{
	matrix retVal(rows, rhs.cols);
	if(cols != rhs.rows) {
		throw matrixException(
			"Matrices cannot be multiplied: Columns and rows are not compatible");
	}
	else {
		for(unsigned int i=0;i<rows;i++) {
			for(unsigned int j=0;j<rhs.cols;j++) {
				retVal[i][j] = 0;
				for(unsigned int k=0;k<rhs.rows;k++) {
					retVal[i][j] += the_matrix[i][k] * rhs[k][j];
				}
			}
		}
	}
	return retVal;
}

matrix matrix::operator*(const double scale) const
{
	matrix retVal(*this);
	for(unsigned int r=0;r<rows;r++) {
		for(unsigned int c=0;c<cols;c++) {
			retVal[r][c] = the_matrix[r][c] * scale;
		}
	}
	return retVal;
}


// Unary operations
matrix matrix::operator~() const
{
	// stub
	matrix retVal(cols, rows);
	for(unsigned int r=0;r<rows;r++) 
	{
		for(unsigned int c=0;c<rows;c++) 
		{
			retVal[r][c] = the_matrix[c][r];
		}
	}
	return retVal;
}
	

void matrix::clear()
{
	for(unsigned int r=0;r<rows;r++) 
	{
		for(unsigned int c=0;c<rows;c++) 
		{
			the_matrix[r][c] = 0.0;
		}
	}
	return;
}

double* matrix::operator[](unsigned int row)
{
	if(row > rows || row < 0) {
		throw matrixException(
			"Cannot access index");
	}
	else {
		return the_matrix[row];
	}
	
}

double* matrix::operator[](unsigned int row) const
{
	if(row > rows || row < 0) {
		throw matrixException(
			"Cannot access index");
	}
	else {
		return the_matrix[row];
	}
}


std::ostream& matrix::out(std::ostream& os) const
{
	string matrixString = "[";
	for(unsigned int r=0;r<rows;r++) 
	{
		matrixString += "[";
		for(unsigned int c=0;c<cols;c++) 
		{
			matrixString += to_string(the_matrix[r][c]);
			if(c<cols-1) {
				matrixString += ",";
			}
		}
		matrixString += "]";
		if(r<rows-1)
		{
			matrixString += ",\n";
		}
	}
	matrixString += "]";
	os << matrixString;
	return os;	
}



// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	return rhs.out(os);
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	matrix retVal(rhs);
	retVal = rhs * scale;
	return retVal;
}