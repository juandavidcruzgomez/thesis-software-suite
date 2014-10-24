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
