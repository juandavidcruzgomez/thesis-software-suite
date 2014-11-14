/**
 The MIT License (MIT)

 Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne 
 juan.cruzgomez@telecom-bretagne.eu

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
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
