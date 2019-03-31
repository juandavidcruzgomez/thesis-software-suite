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
