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
