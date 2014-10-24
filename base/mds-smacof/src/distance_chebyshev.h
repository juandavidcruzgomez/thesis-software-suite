#ifndef CHEBYSHEV_H
#define CHEBYSHEV_H

#include "distance.h"

class ChebyshevDistance : public Distance
{
  friend class DistanceFactory;
protected:
  ChebyshevDistance(){}
  ~ChebyshevDistance(){}
  
public:
  inline float getDistance( const t_point& point_a, const t_point& point_b )
  {
    float result = 0.0f;
    unsigned int size = point_a.dimension;
    for( unsigned int i = 0; i < size; ++i )
    {
      float val = point_a.data[i] - point_b.data[i];
      if( val > result ){
        result = val;
      }
    }
    return result;
  }
};

#endif
