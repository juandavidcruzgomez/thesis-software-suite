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


#include "PoVLayoutDistortion.h"
#include <Model.h>

PoVLayoutDistortion::PoVLayoutDistortion(){
  model = NULL;
}

PoVLayoutDistortion::PoVLayoutDistortion( Model* _model ){
  model = _model;
  viewLayout = model->graph->getLocalProperty<LayoutProperty>("PoV_NULL_viewLayout");
}

PoVLayoutDistortion::~PoVLayoutDistortion(){

}

bool PoVLayoutDistortion::performDistortion( string pov_name ){
  //First, get the border nodes of the NULL pov
  vector<node> border_nodes;
  Role* role = new Role();
  node n;
  forEach( n, model->graph->getNodes() ){
    model->roles_information.getData(n.id,"PoV_NULL",role);
    //cout << "Node " << n.id << ", P-index: " << role->p_index << endl;
    if( role != NULL && role->p_index > 0 ){
      border_nodes.push_back(n);
    }
  }
  //Second, given the border nodes, calculate where do they 
  //belong in the other point of view. Get the centroids!
  calculateCentroids(border_nodes,pov_name);
  //Third, push the nodes...
  map<int,vector<node*> >::iterator centroid_iter;
  Observable::holdObservers();
  LayoutProperty* actualLayout = model->graph->getLocalProperty<LayoutProperty>("viewLayout");
  *actualLayout = *viewLayout;
  for( centroid_iter = centroid_assignation.begin(); centroid_iter != centroid_assignation.end(); centroid_iter++ ){
    int index = (*centroid_iter).first;
    vector<node*> list = (*centroid_iter).second;
    for( int i = 0; i < (int)list.size(); i++ ){
      Coord c = viewLayout->getNodeValue(*list[i]);
      changePosition(*list[i],c,centroid_coords[index],0.75,actualLayout);
    }
  }
  Observable::unholdObservers();
  //Fourth, color!
  
  delete role;
  return true;
}

void PoVLayoutDistortion::calculateCentroids( vector<node> border_nodes, string pov_name ){
  vector<Graph*> sub_groups;
  map<string, int> index;
  //What sub groups?
  Graph* subg;
  int i = 0;
  forEach( subg, model->graph->getSubGraphs() ){
    vector<int> assigned;
    if( (int)subg->getName().find(pov_name) != -1 ){
      centroid_coords[i] = pair<float,float>(0,0);
      int j = 0;
      for( j = 0; j < (int)border_nodes.size(); j++ ){
	if( subg->isElement(border_nodes[j]) ){
	  centroid_assignation[i].push_back(&border_nodes[j]);
	  //assigned.push_back(j);
	}
      }
//       for( j = 0; j < assigned.size(); j++ ){
// 	border_nodes.erase(border_nodes.begin()+assigned[j]);
//       }
      i++;
    }
  }
  //Calculate the coordinates
  //For each centroid...
  map<int,vector<node*> >::iterator centroid_iter;
  for( centroid_iter = centroid_assignation.begin(); centroid_iter != centroid_assignation.end(); centroid_iter++ ){
    int centroid_index = (*centroid_iter).first;
    vector<node*> list = (*centroid_iter).second;
    float x = 0;
    float y = 0;
    for( int i = 0; i < (int)list.size(); i++ ){
      x += viewLayout->getNodeValue(*list[i]).getX();
      y += viewLayout->getNodeValue(*list[i]).getY();
    }
    x /= (float)list.size();
    y /= (float)list.size();
    centroid_coords[centroid_index].first=x;
    centroid_coords[centroid_index].second=y;
    cout << "Centroid " << centroid_index << "=("<<x<<","<<y<<")\n";
  }
}

void PoVLayoutDistortion::changeColors(string pov_name){
}

void PoVLayoutDistortion::changePosition( node n, Coord actual_pos, pair<float,float> centroid, float ratio, LayoutProperty* actualLayout ){
  float new_x = actual_pos.getX();
  float new_y = actual_pos.getY();
  new_x -= centroid.first;
  new_y -= centroid.second;
  new_x *= ratio;
  new_y *= ratio;
  actualLayout->setNodeValue(n, Coord(new_x,new_y,0));
}
