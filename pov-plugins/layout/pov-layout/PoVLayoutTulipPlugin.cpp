/**
 The MIT License (MIT)

 Copyright (c) 2011 Juan David Cruz Gómez and Telecom - Bretagne 
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

#include <tulip/TulipPlugin.h>
#include "CLayoutSpace.h"

class PoVLayoutPlugin : public tlp::LayoutAlgorithm {
public:
    PoVLayoutPlugin( const tlp::PropertyContext &context  ) : tlp::LayoutAlgorithm(context) {
        initialize();
    }

    bool run() {
      try{
        layoutSpace.startAlgorithm();
        float factor = 1600;
        tlp::Iterator<tlp::node> *nodeIter = graph->getNodes();
        while ( nodeIter->hasNext() ) {
            tlp::node n = nodeIter->next();
            tlp::Coord c  = layoutSpace.getPositions()[n];//layout->getNodeValue(n);
            c.setX(c.getX()*factor);
            c.setY(c.getY()*factor);
            layoutResult->setNodeValue(n, c );
        }
        delete nodeIter;
        return true;
      }catch(bad_alloc){
	cerr << "Could not allocate memory... " << __FILE__ << ": " <<__LINE__ << endl;
	return false;
      }
    }

    bool check( std::string &erreurMsg ) {
        erreurMsg="This is not a clustered graph";
        int comCount = 0;
        tlp::Iterator<tlp::Graph*> *subIter = graph->getSubGraphs();
        while ( subIter->hasNext() ) {
            subIter->next();
            comCount++;
        }
        delete subIter;
        return comCount > 0;
    }

private:
    void initialize() {
        if ( graph != NULL ) {
            layoutSpace = CLayoutSpace( graph );
        }
    }

private:
    CLayoutSpace layoutSpace;
};

LAYOUTPLUGINOFGROUP(PoVLayoutPlugin,"Boundary layout","Juan David Cruz Gomez","03/11/2011","Ok","1.0","Clustered");
