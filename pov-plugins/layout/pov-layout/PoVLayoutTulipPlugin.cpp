/**
 *
 * This is the entry point for the PoV layout plugin for Tulip. This
 * implemantation corresponds to the thesis work of Juan David Cruz-Gomez
 * File created on 03/11/2011
 * All rights (and lefts) reserved
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
