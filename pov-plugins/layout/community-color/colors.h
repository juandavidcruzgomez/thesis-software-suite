/**
 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne

 juan.cruzgomez@telecom-bretagne.eu 
 juandavidcruz@gmail.com

 Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
 by the European Commission - subsequent versions of the 
 EUPL (the "Licence");

 You may not use this work except in compliance with the Licence.
 You may obtain a copy of the Licence at:

    https://joinup.ec.europa.eu/software/page/eupl5
  
 Unless required by applicable law or agreed to inwriting, software 
 distributed under the Licence isdistributed on an *"AS IS"* basis,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
 See the Licence for the specific language governing permissions and limitations 
 under the Licence.
*/

#ifndef COLORS_H
#define COLORS_H

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
