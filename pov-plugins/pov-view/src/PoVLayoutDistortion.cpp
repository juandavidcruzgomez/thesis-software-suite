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
