/**
 The MIT License (MIT)

 Copyright (c) 2013 Juan David Cruz Gómez and Telecom - Bretagne 
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
