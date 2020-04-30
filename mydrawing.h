/*
* File: mydrawing.h
* Author: Jacob Christensen
* Course: CS3210
* Date: 04/20/19
*/

#ifndef _MY_DRAWING_H
#define _MY_DRAWING_H

#include "drawbase.h"
#include "image.h"
#include "matrix.h"
#include "viewcontext.h"

// forward reference
class GraphicsContext;

class MyDrawing: public DrawingBase
{
public:
	// Enum that defines possible drawing modes
	enum shapeMode {POINT, LINE, TRIANGLE};

	// Empty Constructor
	MyDrawing();
	// Destructor
	~MyDrawing();
	virtual void paint(GraphicsContext* gc);
	// Event handler for clicking the mouse button down
	virtual void mouseButtonDown(GraphicsContext* gc, unsigned int button,
								 int x, int y);
	// Event handler for releasing the mouse button
	virtual void mouseButtonUp(GraphicsContext* gc, unsigned int button,
								 int x, int y);
	// Event handler for moving the mouse
	virtual void mouseMove(GraphicsContext* gc, int x, int y);
	// Event handler pressing a keyboard key down
	virtual void keyDown(GraphicsContext* gc, unsigned int keycode);
	// Event handler for releasing a keyboard key
	virtual void keyUp(GraphicsContext* gc, unsigned int keycode);	

private:
	//Keycodes for switching modes, saving, and loading
	const unsigned int P = 112;
	const unsigned int L = 108;
	const unsigned int T = 116;
	const unsigned int S = 115;
	const unsigned int D = 100;
	const unsigned int R = 114;
	const unsigned int LEFT_ARR = 65361;
	const unsigned int UP_ARR = 65362;
	const unsigned int RIGHT_ARR = 65363;
	const unsigned int DOWN_ARR = 65364;
	const unsigned int CCW_RO = 44;
	const unsigned int CW_RO = 46;


	// Possible coordinates
	int x0, y0, x1, y1, x2, y2;
	// Current color
	unsigned int color;
	// Image holding all of the shapes being drawn
	image img;
	// Enum to keep track of the drawing mode the program is in
	shapeMode mode;
	// ViewContext for displaying and transforming image
	ViewContext vc;
};


#endif