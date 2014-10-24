/*
 <one line to give the program's name and a brief idea of what it does.>
 Copyright (C) 2014  Juan David Cruz Gomez <email>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __DISTANCE_H__
#define __DISTANCE_H__

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
