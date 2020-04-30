/*
* File: main.cpp
* Author: Jacob Christensen
* Course: CS3210
* Date: 03/29/19
* 
* D = load in STL file and draw
* Arrow Keys = rotation/orbiting
* Scroll wheel = scaling
* Numbers = change focus distance option
*/

#include "shape.h"
#include "x11context.h"
#include <unistd.h>
#include <iostream>
#include "mydrawing.h"
int main(void)
{
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);
	gc->setColor(GraphicsContext::GREEN);
	// make a drawing
	MyDrawing md;
	// start event loop - this function will return when X is clicked
	// on window
	gc->runLoop(&md);
	delete gc;
	return 0;
}