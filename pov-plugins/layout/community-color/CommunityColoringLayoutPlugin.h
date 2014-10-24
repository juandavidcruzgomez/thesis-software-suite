/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Juan David Cruz Gomez <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef COMMUNITYCOLORINGLAYOUTPLUGIN_H
#define COMMUNITYCOLORINGLAYOUTPLUGIN_H

#include <tulip/TulipPlugin.h>
#include <tulip/Color.h>
#include "colors.h"

namespace {
const char * paramHelp[] = {
  // property
  HTML_HELP_OPEN() \
  HTML_HELP_DEF( "type", "ColorProperty" ) \
  HTML_HELP_BODY() \
  "This is the property for storing the color value of the graph" \
  HTML_HELP_CLOSE(),
  // property
  HTML_HELP_OPEN() \
  HTML_HELP_DEF( "type", "bool" ) \
  HTML_HELP_BODY() \
  "This propertèy indicates whether the colors are continuous or not" \
  HTML_HELP_CLOSE(),
};
}

class CommunityColoringLayoutPlugin : public tlp::ColorAlgorithm
{

public:
    CommunityColoringLayoutPlugin( const tlp::PropertyContext &context );
    virtual ~CommunityColoringLayoutPlugin();
    /**
     * Implements the run method to called by the plugin manager
     */
    bool run();
    /**
     * Implements the check method to by ran by the plugin manager
     */
    bool check(std::string &errorMsg );
private:
  bool intercalated;
};

#endif // COMMUNITYCOLORINGLAYOUTPLUGIN_H
