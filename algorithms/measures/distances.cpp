#include "distances.h"

double euclidean_distance( std::vector<double>& vec_a, std::vector<double>& vec_b )
{
  double result = 0;
  for( unsigned int i = 0; i < vec_a.size(); i++ )
  {
    result += ( vec_a[i] - vec_b[i] ) * ( vec_a[i] - vec_b[i] );
  }
  return sqrt(result);
}

double cosine_distance( std::vector<double>& vec_a, std::vector<double>& vec_b )
{
  double result = 0;
  double inner_p = inner_product( vec_a, vec_b );
  double norm_a = norm( vec_a );
  double norm_b = norm( vec_b );
  if( norm_a > 0 && norm_b > 0 )
  {
    result = inner_p / ( norm_a * norm_b );
  }
  return result;
}

double inner_product( std::vector<double>& vec_a, std::vector<double>& vec_b )
{
  double result = 0;
  for( unsigned int i = 0; i < vec_a.size(); i++ )
  {
    result += vec_a[i] * vec_b[i];
  }
  return result;
}

double norm( std::vector<double>& vec_a )
{
  double result = 0;
  for( unsigned int i = 0; i < vec_a.size(); i++ )
  {
    result += vec_a[i] * vec_a[i];
  }
  return sqrt(result);
}
