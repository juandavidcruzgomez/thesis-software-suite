/**
 The MIT License (MIT)

 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne 
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
