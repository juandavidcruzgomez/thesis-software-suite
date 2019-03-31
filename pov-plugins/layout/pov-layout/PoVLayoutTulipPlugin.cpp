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
