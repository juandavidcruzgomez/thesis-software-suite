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
#include "distance_factory.h"


Distance* DistanceFactory::buildDistanceCalculator( int type )
{
  switch( type )
  {
    case( MANHATTAN ):
      return new ManhattanDistance();
      break;
    case( EUCLIDEAN ):
      return new EuclideanDistance();
      break;
    case( CHEBYSHEV ):
      return new ChebyshevDistance();
      break;
    default:
      cerr << "That's not a valid distance. Using Euclidean instead.\n";
      return new EuclideanDistance();
      break;
  }
}
