/*
 *  util.cpp
 *  MultidimensionalScaling
 *
 *  Created by Juan David CRUZ GOMEZ on 9/20/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
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

