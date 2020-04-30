/*
* File: mydrawing.cpp
* Author: Jacob Christensen
* Course: CS3210
* Date: 04/20/19
*/

#include "mydrawing.h"
#include "gcontext.h"
#include "viewcontext.h"
#include "matrix.h"
#include "triangle.h"
#include "line.h"

#include <fstream>
#include <iostream>

using namespace std;

// Constructor
MyDrawing::MyDrawing()
{
	color = GraphicsContext::GREEN;
	x0 = x1 = y0 = y1 = x2 = y2 = 0;
	return;
}

MyDrawing::~MyDrawing() {}

void MyDrawing::paint(GraphicsContext* gc)
{
	int middlex = gc->getWindowWidth()/2;
	int middley = gc->getWindowHeight()/2;

	gc->setColor(GraphicsContext::MAGENTA);
	
	for (int yi=middley-50;yi<=middley+50;yi++)
	{
		gc->drawLine(middlex-50,yi,middlex+50,yi);
	}
	
	gc->setColor(GraphicsContext::GREEN);
	// redraw the line if requested
	gc->drawLine(x0,y0,x1,y1);
	return;
}

void MyDrawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y)
{
	if(button == 4) {
		// Scale the viewport by a factor of 2
		vc.scale(2);
		gc->clear();
		img.draw(gc,vc);
	}
	else if(button == 5) {
		// Scale the viewport by a factor of 1/2
		vc.scale(0.5);
		gc->clear();
		img.draw(gc,vc);
	}
	
	return;
}

void MyDrawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
	return;
}

void MyDrawing::mouseMove(GraphicsContext* gc, int x, int y)
{
	
	return;
}

// Do nothing on key down
void MyDrawing::keyDown(GraphicsContext* gc, unsigned int keycode) {}

// Respond to keypress on keyUp
void MyDrawing::keyUp(GraphicsContext* gc, unsigned int keycode) {
	if(keycode == this->S) {
		ofstream output_file;
		output_file.open("image_out.txt", ofstream::trunc);
		output_file << img;
		output_file.close();
	}
	// Load the image described in image_in.txt
	else if(keycode == this->D) {
		vc.reset(gc);
		img.erase(img);
		gc->clear();
		vc.translate(400,-300);
		ifstream input_file("image_in.txt");
		input_file >> img;
		input_file.close();
		img.draw(gc, vc);
	}
	// Reset the viewport to its original coordinates
	else if(keycode == this->R) {
		vc.reset(gc);
		vc.translate(400,-300);
		img.draw(gc,vc);
	}
	// Vertical and horizontal orbit controls
	else if(keycode == this->RIGHT_ARR) {
		vc.rotate_H(10);
		gc->clear();
		img.draw(gc,vc);
	}
	else if(keycode == this->LEFT_ARR) {
		vc.rotate_H(-10);
		gc->clear();
		img.draw(gc,vc);
	}
	else if(keycode == this->UP_ARR) {
		vc.rotate_V(-10);
		gc->clear();
		img.draw(gc,vc);
	}
	else if(keycode == this->DOWN_ARR) {
		vc.rotate_V(10);
		gc->clear();
		img.draw(gc,vc);
	}
	// Change the current focus distance
	else if(keycode > 48 && keycode < 58){
		switch(keycode) {
			case 49 :
				vc.setFocus(15.0);
				gc->clear();
				img.draw(gc,vc);
				break;
			case 50 :
				vc.setFocus(20.0);
				gc->clear();
				img.draw(gc,vc);
				break;
			case 51 :
				vc.setFocus(30.0);
				gc->clear();
				img.draw(gc,vc);
				break;
			case 52 :
				vc.setFocus(40.0);
				gc->clear();
				img.draw(gc,vc);
				break;
			case 53 :
				vc.setFocus(50.0);
				gc->clear();
				img.draw(gc,vc);
				break;
			case 54 :
				vc.setFocus(60.0);
				gc->clear();
				img.draw(gc,vc);
				break;
			case 55 :
				vc.setFocus(70.0);
				gc->clear();
				img.draw(gc,vc);
				break;
			case 56 :
				vc.setFocus(80.0);
				gc->clear();
				img.draw(gc,vc);
				break;
			case 57 :
				vc.setFocus(90.0);
				gc->clear();
				img.draw(gc,vc);
				break;
		}
	}
	return;
}