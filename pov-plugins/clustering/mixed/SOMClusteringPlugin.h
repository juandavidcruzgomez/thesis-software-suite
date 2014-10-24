/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Juan David Cruz Gomez <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef SOMCLUSTERINGPLUGIN_H
#define SOMCLUSTERINGPLUGIN_H

#include <map>
#include <vector>

#include <tulip/TulipPlugin.h>
#include "somclusteringspace.h"

using namespace std;
using namespace tlp;

/** \addtogroup clustering*/
/*@{*/

class SOMClusteringPlugin : public tlp::Algorithm{
public:
  /**
   * Constructor
   * @param context : the algorithm context
   */
  SOMClusteringPlugin( tlp::AlgorithmContext context );
  /**
   * Destructor
   */
  ~SOMClusteringPlugin();
  /**
   * Executes the algorithm
   */
  bool run();
  /**
   * Check if all the data is available to execute the algorithm
   */
  bool check(string& error);
  /**
   * Reset the algorithm
   */
  void reset();
  
  void assignEdgesToGroups();
  
};

/*@}*/

#endif // SOMCLUSTERINGPLUGIN_H
