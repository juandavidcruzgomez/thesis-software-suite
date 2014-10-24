/*
 * colors.h
 * This file is part of the PhD thesis of Juan David Cruz Gomez.
 * Copyright Juan David Cruz Gomez - Telecom Bretagne
 * Brest, France
 *  Created on: May 8, 2011
 *      Author: juandavidcruz
 */

#ifndef COLORS_H_
#define COLORS_H_

#define PI 3.141592654

#include <math.h>

/**
 * Paint it black!
 * @param angle
 * @param rgb
 */
inline void angle2RGB( double angle, double rgb[3] ){
	double auxangle = 0;

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


#endif /* COLORS_H_ */