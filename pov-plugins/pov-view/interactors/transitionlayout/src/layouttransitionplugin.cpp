/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Juan David Cruz Gomez <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "layouttransitionplugin.h"

LayoutTransitionPlugin::LayoutTransitionPlugin( const tlp::PropertyContext &context ): LayoutAlgorithm(context)
{
  addParameter<LayoutProperty>("Initial layout", paramHelp[0], "viewLayout");
  addParameter<LayoutProperty>("Target layout", paramHelp[1], "viewLayout");
  addParameter<int>("Steps", paramHelp[2], "100");
  if( graph != NULL ){
    pluginProgress->setPreviewMode(true);
    pluginProgress->showPreview(true);
  }
}

LayoutTransitionPlugin::~LayoutTransitionPlugin()
{

}

bool LayoutTransitionPlugin::run(){
  LayoutProperty* startLayout = 0;
  LayoutProperty* endLayout = 0;
  int steps = 100;
  dataSet->get("Initial layout", startLayout );
  dataSet->get("Target layout", endLayout );
  dataSet->get<int>("Steps", steps );
  map<int,float*> values;
  startLayout = graph->getLocalProperty<LayoutProperty>(startLayout->getName());
  endLayout = graph->getLocalProperty<LayoutProperty>(endLayout->getName());
  node n;
  Observable::holdObservers();
  forEach( n, graph->getNodes() ){
    float start_x = startLayout->getNodeValue(n).getX();
    float start_y = startLayout->getNodeValue(n).getY();
     layoutResult->setNodeValue(n,Coord(start_x,start_y,0));
    float end_x = endLayout->getNodeValue(n).getX();
    float end_y = endLayout->getNodeValue(n).getY();
    float m = calculate_slope(start_x,start_y,end_x,end_y);
    float delta = (end_x-start_x)/(float)steps;
    float* value = new float[4];
    value[0] = delta;
    value[1] = m;
    value[2] = end_x;
    value[3] = end_y;
    values[n.id] = value;
  }
  Observable::unholdObservers();
//Now, change the layout...
  int i = 0;
  while( i < steps ){
    Observable::holdObservers();
    forEach( n, graph->getNodes() ){
      float x = layoutResult->getNodeValue(n).getX();
      float y = layoutResult->getNodeValue(n).getY();
      
      x += values[n.id][0];
      y = values[n.id][1]*(x-values[n.id][2])+values[n.id][3];
      layoutResult->setNodeValue(n,Coord(x,y,0));
    }
    Observable::unholdObservers();
    i++;
    pluginProgress->progress(i,steps);
  }
    values.clear();
  return pluginProgress->state() != TLP_CANCEL;
}

bool LayoutTransitionPlugin::check( std::string &erreurMsg ){
  return true;
}

float LayoutTransitionPlugin::calculate_slope( float x1, float y1, float x2, float y2 ){
  return x1-x2 != 0 ? (y2-y1)/(x2-x1) : 1E34;
}

float LayoutTransitionPlugin::calculate_distance( float x1, float y1, float x2, float y2 ){
  float dist = 0;
  dist = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
  return (float)sqrt(dist);
}
