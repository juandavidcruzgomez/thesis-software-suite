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

