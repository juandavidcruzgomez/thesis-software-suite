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

#ifndef DISTANCE_H
#define DISTANCE_H

#include <math.h>


typedef struct point {
  float* data;
  unsigned int dimension;
  point( float* _data, unsigned int _dimension )
  {
    dimension = _dimension;
    data = 0;
    data = new float[dimension];
    if( _data == 0 )
    { 
      for( unsigned int i = 0; i < dimension; ++i )
      {
        data[i] = 0.0f;
      }
    }else {
      for( unsigned int i = 0; i < dimension; ++i )
      {
        data[i] = _data[i];
      }
    }

  }
  ~point()
  {
    if( data != 0 )
    {
      delete[] data;
      data = 0;
    }
  }
} t_point;


class Distance
{
public:
  Distance(){}
  virtual ~Distance(){}
  /**
   * Computes the distance between two points. This is an abstract fucntion to 
   * be implemented for specific computations.
   * @param point_a the first point
   * @param point_b the second point
   * @return the distance
   */
  virtual float getDistance( const t_point& point_a, const t_point& point_b ) = 0;
    
};

#endif
