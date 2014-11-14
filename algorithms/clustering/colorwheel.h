/**
 The MIT License (MIT)

 Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne 
 juan.cruzgomez@telecom-bretagne.eu

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#define PI 3.141592654

#include <math.h>

/**
 * It is easy. For a given angle the procedure will find a RGB vector. Because colors are awesome!
 * Paint it black!
 * @param angle
 * @param rgb
 */
inline void angle2RGB( float angle, float rgb[3] ){
	float auxangle = 0;
	
	if( angle < 0.0 ){
		angle += 2*PI;
	}
	
	if( angle <= PI/3.0 ){
		auxangle = 3.0 * angle/4.0;
		rgb[0] = 1.0;
		rgb[1] = tan( auxangle );
		rgb[2] = 0.0;
	}else if( angle <= 2.0*PI/3.0 ){
		auxangle = 3.0 * angle/4.0;
		rgb[0] = cos( auxangle ) / sin( auxangle );
		rgb[1] = 1.0;
		rgb[2] = 0.0;
	}else if( angle <= PI ){
		auxangle = 3.0 * ( angle - (2.0*PI/3.0) )/4.0;
		rgb[0] = 0.0;
		rgb[1] = 1.0;
		rgb[2] = tan( auxangle );
	}else if( angle <= 4.0*PI/3.0 ){
		auxangle = 3.0 * ( angle - (2.0*PI/3.0) )/4.0;
		rgb[0] = 0.0;
		rgb[1] = cos( auxangle ) / sin( auxangle );
		rgb[2] = 1.0;
	}else if( angle <= 5.0*PI/3.0 ){
		auxangle = 3.0 * ( angle - (4.0*PI/3.0) )/4.0;
		rgb[0] = tan( auxangle );
		rgb[1] = 0.0;
		rgb[2] = 1.0;
	}else if( angle <= 2.0*PI ){
		auxangle = 3.0 * ( angle - (4.0*PI/3.0) )/4.0;
		rgb[0] = 1.0;
		rgb[1] = 0.0;
		rgb[2] = cos( auxangle ) / sin( auxangle );
	}
}

#endif
