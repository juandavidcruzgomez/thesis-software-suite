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
