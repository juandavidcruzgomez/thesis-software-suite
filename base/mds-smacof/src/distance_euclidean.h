#ifndef __EUCLIDEAN_H__
#define __EUCLIDEAN_H__

#include "distance.h"



class EuclideanDistance : public Distance
{
  friend class DistanceFactory;
protected:
  EuclideanDistance(){}
  ~EuclideanDistance(){}
  
public:
  inline float getDistance( const t_point& point_a, const t_point& point_b )
  {
    float result = 0.0f;
    unsigned int size = point_a.dimension;
    for( unsigned int i = 0; i < size; ++i )
    {
      float d1 = point_a.data[i];
      float d2 = point_b.data[i];
      result += (d1-d2)*(d1-d2);
    }
    return sqrt(result);
  }
};

#endif
