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


#ifndef LAYOUTTRANSITIONPLUGIN_H
#define LAYOUTTRANSITIONPLUGIN_H

#include <tulip/LayoutAlgorithm.h>
#include <tulip/TulipPlugin.h>

#include <tulip/LayoutProperty.h>
#include <tulip/ForEach.h>
#include <map>


namespace {
const char * paramHelp[] = {
  // 
  HTML_HELP_OPEN() \
  HTML_HELP_DEF( "type", "layout" ) \
  HTML_HELP_DEF( "default", "viewLayout" ) \
  HTML_HELP_BODY() \
  "The initial layout to start with the transition" \
  HTML_HELP_CLOSE(),
  HTML_HELP_OPEN() \
  HTML_HELP_DEF( "type", "layout" ) \
  HTML_HELP_DEF( "default", "viewLayout" ) \
  HTML_HELP_BODY() \
  "The target layout" \
  HTML_HELP_CLOSE(),
  HTML_HELP_OPEN() \
  HTML_HELP_DEF( "type", "int" ) \
  HTML_HELP_DEF( "default", "100" ) \
  HTML_HELP_BODY() \
  "The number of steps to change the positions" \
  HTML_HELP_CLOSE(),
};
}

using namespace std;
using namespace tlp;

class LayoutTransitionPlugin : public tlp::LayoutAlgorithm{

public:
    LayoutTransitionPlugin( const tlp::PropertyContext &context );
    virtual ~LayoutTransitionPlugin();
    bool run();

    bool check( std::string &erreurMsg );
    
private:
  float calculate_slope( float x1, float y1, float x2, float y2 );
  
  float calculate_distance( float x1, float y1, float x2, float y2 );
};

LAYOUTPLUGINOFGROUP(LayoutTransitionPlugin,"Transition layout","Juan David Cruz Gomez","31/08/2012","Ok","1.0","Basic");
#endif // LAYOUTTRANSITIONPLUGIN_H
