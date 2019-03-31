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
#ifndef DIST_FACTORY_H
#define DIST_FACTORY_H

#include <iostream>

#include "distance.h"
#include "distance_euclidean.h"
#include "distance_manhattan.h"
#include "distance_chebyshev.h"

#define MANHATTAN 1
#define EUCLIDEAN 2
#define CHEBYSHEV 3


using namespace std;

class DistanceFactory
{
protected:
  DistanceFactory(){}
  ~DistanceFactory(){}
  
public:
  static Distance* buildDistanceCalculator( int type );
};

#endif
