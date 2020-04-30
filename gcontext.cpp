/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#define _USE_MATH_DEFINES	// for M_PI
#include <cmath>	// for trig functions
#include "gcontext.h"	

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}


/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	
	// find slope
	int dx = x1-x0;
	int dy = y1-y0;
	
	// make sure we actually have a line
	if (dx != 0 || dy !=0)
	{
		int xi, yi, xi1, yi1, di, di1;
		// slope < 1?
		if (std::abs(dx)>std::abs(dy))
		{	
			xi = x0;
			yi = y0;
			di = 2*std::abs(dy) - std::abs(dx);
			setPixel(xi,yi);

			while(xi != x1) {
				// Always increment/decrement the x-value
				if(xi < x1) {
					xi1 = xi + 1;
				}
				else{
					xi1 = xi - 1;
				}
				
				// Calculate the new decision matrix
				if(di < 0 || di == 0) {
					// If di is negative or zero, keep the same y-value
					yi1 = yi;
					di1 = di + 2 * std::abs(dy);
				}
				else {
					// If di is non-negative, increment the y-value
					if(dy > 0) {
						yi1 = yi + 1;
					}
					// Otherwise, decrement the y-value
					else {
						yi1 = yi - 1;
					}
					di1 = di + 2 * std::abs(dy) - 2 * std::abs(dx);
				}
				setPixel(xi, yi);
				xi = xi1;
				yi = yi1;
				di = di1;
			}

		} // end of if |slope| < 1 
		else 
		{	
			xi = x0;
			yi = y0;
			di = 2*std::abs(dx) - std::abs(dy);
			setPixel(xi,yi);

			while(yi != y1) {
				// Always increment/decrement the y-value
				if(yi < y1) {
					yi1 = yi + 1;
				}
				else{
					yi1 = yi - 1;
				}
				
				// Calculate the new decision matrix
				if(di <= 0) {
					// If di is negative, keep the same x-value
					xi1 = xi;
					di1 = di + 2 * std::abs(dx);
				}
				else {
					// If di is non-negative, increment the x-value
					if(dx > 0) {
						xi1 = xi + 1;
					}
					// Otherwise, decrement the x-value
					else {
						xi1 = xi - 1;
					}
					di1 = di + 2 * std::abs(dx) - 2 * std::abs(dy);
				}
				setPixel(xi, yi);
				xi = xi1;
				yi = yi1;
				di = di1;
			} 
		} // end of else |slope| >= 1
	} // end of if it is a real line (dx!=0 || dy !=0)
	return;
}



/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin/center of circle
 *  radius - radius of circle
 * 
 * Returns: void
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	// Declaring variables to be useed
	int xi, xi1, yi, yi1, pi, pi1;
	// Check if there is a valid radius
	if(radius <= 0) {
		// If radius is <= 0, then only set one pixel
		setPixel(x0,y0);
	}
	else {
		// Initial values for the variables 
		xi = x0;
		yi = radius + y0;
		pi = 1 - (radius);
		//Sweep the x-values
		while((xi-x0)<(yi-y0 + 1)) {
			xi1 = xi + 1;
			// If decision matrix is negative
			if(pi<0) {
				// Y doesn't change
				yi1 = yi;
				pi1 = pi + (2 * (xi1 - x0)) + 1;
			}
			// If decision matrix is positive
			else {
				// Y increments
				yi1 = yi - 1;
				pi1 = pi + (2 * ((xi1 - x0) - (yi1 - y0))) + 1;
			}
			// Set the pixels
			setPixel(xi,yi);
			setPixel(x0-(xi-x0),yi);
			setPixel(xi,y0-(yi-y0));
			setPixel(x0-(xi-x0),y0-(yi-y0));
			// Move to the next values
			xi = xi1;
			yi = yi1;
			pi = pi1;
		}
		yi = y0;
		xi = x0 +  radius;
		pi = 1 - (radius);
		//Sweep the y-values
		while((xi-x0 + 1)>(yi-y0)) {
			yi1 = yi +1;
			// If decision matrix is negative
			if(pi<0) {
				// X doesn't change
				xi1 = xi;
				pi1 = pi + (2 * (yi1 - y0)) + 1;
			}
			// If decision matrix is positive
			else {
				// X decrements
				xi1 = xi - 1;
				pi1 = pi + (2 * ((yi1 - y0) - (xi1 - x0))) + 1;
			}
			// Set the pixels
			setPixel(xi,yi);
			setPixel(x0-(xi-x0),yi);
			setPixel(xi,y0-(yi-y0));
			setPixel(x0-(xi-x0),y0-(yi-y0));
			// Move to the next values
			xi = xi1;
			yi = yi1;
			pi = pi1;
		}
	}
	return;	
}

void GraphicsContext::endLoop()
{
	run = false;
}


