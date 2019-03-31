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
