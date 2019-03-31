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
