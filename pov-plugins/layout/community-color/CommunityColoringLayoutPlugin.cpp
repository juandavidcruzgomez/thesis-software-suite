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


#include "CommunityColoringLayoutPlugin.h"

COLORPLUGIN( CommunityColoringLayoutPlugin, "Community Coloring", "Juan David Cruz Gomez", "01/03/2013", "Community coloring plugin", "1.0" );

CommunityColoringLayoutPlugin::CommunityColoringLayoutPlugin(const tlp::PropertyContext& context) : tlp::ColorAlgorithm(context)
{
  addParameter<bool>("Intercalated", paramHelp[1], "false" );
  intercalated = false;
}

CommunityColoringLayoutPlugin::~CommunityColoringLayoutPlugin(){}

bool CommunityColoringLayoutPlugin::run(){
  float communities_count = graph->numberOfSubGraphs();
  float angle_step = 2.0*PI/communities_count;
  float angle = 0;
  int counter = 0;
  tlp::Iterator<tlp::Graph*> *subIter = graph->getSubGraphs();
  tlp::Iterator<tlp::node>* nodes= 0;
  if( dataSet != 0 ){
      dataSet->get("Intercalated", this->intercalated );
  }
  tlp::Observable::holdObservers();
  while( subIter->hasNext() ){
      tlp::Graph* actualSubGraph = subIter->next();
      double rgb[3];
      rgb[0] = 0.0;
      rgb[1] = 0.0;
      rgb[2] = 0.0;
       //Intercalated or not
      if( intercalated ){
	angle2RGB( angle+(PI/2.0)*(counter % 2 ), rgb );
      }else{
	angle2RGB( angle, rgb );
      }
      nodes = actualSubGraph->getNodes();
      while( nodes->hasNext() ){
	tlp::node n = nodes->next();
	colorResult->setNodeValue(n,tlp::Color(rgb[0]*255.0, rgb[1]*255.0, rgb[2]*255.0) );
      }
      angle += angle_step;
      counter++;
  }
  if( nodes != 0 ){
    delete nodes;
  }
  delete subIter;
  colorResult->setAllEdgeValue(tlp::Color(0,0,0,15));
  tlp::Observable::unholdObservers();
  return true;
}

bool CommunityColoringLayoutPlugin::check(std::string &errorMsg ){
  errorMsg = "The graph does not contain subgraphs to be colored!";
  int communities_count = graph->numberOfSubGraphs();
  return !(communities_count==0);
}
