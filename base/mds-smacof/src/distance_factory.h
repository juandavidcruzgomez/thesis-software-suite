/**
 Creates different types of distance measure methods
 Copyright (C) 2014 Juan David Cruz Gomez juandavidcruz_at_gmail_dot_com
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef DIST_FACTORY_H
#define DIST_FACTORY_H

#include <iostream>

#include "distance.h"
#include "distance_euclidean.h"
#include "distance_manhattan.h"
#include "distance_chebyshev.h"

#define MANHATTAN  1
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
