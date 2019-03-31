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
#ifndef MANHATTAN_H
#define MANHATTAN_H

#include "distance.h"



class ManhattanDistance : public Distance
{
  friend class DistanceFactory;
protected:
  ManhattanDistance(){}
  ~ManhattanDistance(){}
  
public:
  inline float getDistance( const t_point& point_a, const t_point& point_b )
  {
    float result = 0.0f;
    unsigned int size = point_a.dimension;
    for( unsigned int i = 0; i < size; ++i )
    {
      float val = point_a.data[i] - point_b.data[i];
      result += val < 0 ? -1.0*val : val;
    }
    return result;
  }
};

#endif
