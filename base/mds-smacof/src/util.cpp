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

#include "util.h"

Matrix* createDissimilarityMatrix( std::vector<t_point*> point_set, int distance_type )
{
  Matrix* result = 0;
  unsigned int size = point_set.size();
  if( size > 0 )
  {
    Distance* dist = DistanceFactory::buildDistanceCalculator(distance_type);
    result = new Matrix( size, size, COLUMN_MAJOR );
    result->set_all_zeros();
    for( unsigned int i = 0; i < size; ++i )
    {
      for(unsigned int j = i; j < size; ++j )
      {
        if( i != j )
        {
          float distance = dist->getDistance(*point_set.at(i), *point_set.at(j));
          result->setElement(i, j, distance );
          result->setElement(j, i, distance );
        }
      }
    }
    delete dist;
  }
  return result;
}

