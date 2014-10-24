/*
 *  Model.cpp
 *  PoVIntegratorViewPlugin
 *
 *  Created by Juan David CRUZ GOMEZ on 6/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Model.h"
#include "Controller.h"
#include <tulip/LayoutProperty.h>
#include <tulip/SizeProperty.h>

Model::Model() {
    controller = NULL;
    graph = NULL;
    loader = NULL;
    nb_pov = 0;
}

void Model::setController( Controller* _controller ) {
    controller = _controller;
}

void Model::setData( Graph* _graph, DataSet _data ) {
    graph = _graph;
    data = _data;
    roles_information = GeneralPoVInfoContainer<Role*>(graph->numberOfNodes());
}

SemanticPatternLoader* Model::getLoader() const {
    return loader;
}

//Messages from the controller//
void Model::loadFeaturesAction( string filename ) {
    loader = new SemanticPatternLoader(filename.c_str());
    loader->loadPatterns(true);
    finishedFeaturesLoad( filename );
}

void Model::createGraphProperty( map<int, vector<double> > properties ) {
    if ( graph != NULL ) {
        Observable::holdObservers();
        nb_pov = properties[0][0];
        DoubleVectorProperty* pov_prop = graph->getLocalProperty<DoubleVectorProperty>("PoV");
        node n;
        forEach( n, graph->getNodes() ) {
            pov_prop->setNodeValue(n, properties[n.id]);
        }
        Observable::unholdObservers();
        controller->povPropertyCreated(nb_pov);
    }
}

void Model::executeCommunityDetection() {
    string errMsg;
    data.set<bool>("signature",true);
    //Calculate the communities for each point of view
    int* weights = new int[graph->numberOfEdges()];
    IntegerProperty* group = NULL;
    //First, for the point of view null
    data.set<string>("name","PoV_NULL");
    data.set<int*>("weights", NULL );
    graph->applyAlgorithm("PoV Community Detection", errMsg, &data, NULL);
    double q = 0;
    data.get("finalModularity", q );
    modularities["PoV_NULL"] = q;
    nb_communities["PoV_NULL"] = getNumberOfSubGroups("PoV_NULL");
    calculateRoles("PoV_NULL");
    graph->holdObservers();
    cout << "PoVs: " << nb_pov << endl;
    for ( int i = 0; i < nb_pov; i++ ) {
        string subname("PoV_");
        string povname("PoV_");
        char index[8];
        sprintf(index, "%d", i );
        povname.append(index).append("_SOM_Group");
        subname.append(index);
        data.set<string>("name",subname);
        if ( graph->existLocalProperty(povname) ) {
            group = graph->getLocalProperty<IntegerProperty>(povname);
            edge e;
            forEach(e,graph->getEdges()) {
                node source = graph->source(e);
                node target = graph->target(e);
                if ( group->getNodeValue(source) == group->getNodeValue(target) ) {
                    weights[e.id] = 20;
                } else {
                    weights[e.id] = 1;
                }
            }
            data.set<int*>("weights", weights );
            graph->applyAlgorithm("PoV Community Detection", errMsg, &data, NULL);
            double q = 0;
            data.get("finalModularity", q );
            modularities[subname] = q;
            nb_communities[subname] = getNumberOfSubGroups(subname);
	    calculateRoles(subname);
        }
    }
    calculateCommunitiesComposition();
    graph->unholdObservers();
    finishedCommunityDetection();
}

void Model::executeDataClustering() {
    string errMsg;
    graph->applyAlgorithm("SOM clustering algorithm",errMsg,&data,NULL);
    finishedSOMProcessing();
}

void Model::executeIndicesGeneration() {}

void Model::executeLayouts() {
    string errMsg;
    //Execute the layout for the NULL pov
    LayoutProperty* layout;
    LayoutProperty* viewLayout = graph->getLocalProperty<LayoutProperty>("viewLayout");
    data.set<bool>("signature",true);
    data.set<string>("prefix","PoV_NULL_");
    graph->applyPropertyAlgorithm("PoV Layout", viewLayout,errMsg,NULL,&data);
    //Now for each point of view
    for ( int i = 0; i < nb_pov; i++ ) {
        //First, create the properties associated to the layout.
        string layoutprop("PoV_");
        string sizeprop("PoV_");
        string typeprop("PoV_");
        string groupprop("PoV_");
        char index[8];
        sprintf(index, "%d", i );
        layoutprop.append(index).append("_viewLayout");
        sizeprop.append(index).append("_viewSize");
        typeprop.append(index).append("_nodeType");
        groupprop.append(index).append("_");
        //Prepare the data
        data.set<string>("prefix",groupprop);
        layout = graph->getLocalProperty<LayoutProperty>(layoutprop);
        //Execute the algorithm
        graph->applyPropertyAlgorithm("PoV Layout", layout,errMsg,NULL,&data);
    }
    controller->layoutIsFinished();
}

void Model::measureLayouts() {}

void Model::executeAll() {
    executeDataClustering();
    executeCommunityDetection();
    executeIndicesGeneration();
    executeLayouts();
    measureLayouts();
    //layout of layouts?
}

void  Model::changeActiveLayout( string povprefix ) {
    string name = povprefix.append("_viewLayout");
    if ( graph->existLocalProperty(name) ) {
        //Change it
        Observable::holdObservers();
        LayoutProperty* source = graph->getLocalProperty<LayoutProperty>(name);
        LayoutProperty* target = graph->getLocalProperty<LayoutProperty>("viewLayout");
        *target = *source;
        Observable::unholdObservers();
    } else {
        //Inform the controller...
        controller->layoutPropertyError( name );
    }
}

void Model::calculateDegreeDistribution( map<int,int> & data ) {
    if ( graph != NULL && graph->numberOfNodes() > 0 ) {
        node n;
        forEach( n, graph->getNodes() ) {
            int degree = graph->deg(n);
            if ( data.count(degree) > 0 ) {
                data[degree]++;
            } else {
                data[degree] = 1;
            }
        }
    }
}

void Model::getACommunityComposition( string pov_name, vector<map<int,int> >& data ) {
    if ( proportions.count(pov_name) > 0 ) {
        data = proportions[pov_name];
    }
}

void Model::getModularityEntropy( string pov_name, float& modularity, float& entropy ){
  if( modularities.count(pov_name) > 0 ){
    modularity = modularities[pov_name];
  }
}

void Model::getRolesFromPov( map<int, Role*>& data, string pov_name ){
  node n;
  forEach( n, graph->getNodes() ){
    Role* r = new Role();
    roles_information.getData(n.id,pov_name,r);
    data[n.id] = r;
  }
}

void Model::performDistortion( string pov_name ){
  PoVLayoutDistortion dist(this);
  dist.performDistortion(pov_name);
}
//Messages to the controller//
void Model::finishedFeaturesLoad( string &filename ) {
    if ( controller != NULL ) {
        controller->featuresLoaded(filename,loader->getPatternSize(), loader->getHeaderLabels() );
    }
}

void Model::finishedCommunityDetection() {
    controller->communityDetectionFinished(nb_communities["PoV_NULL"],modularities["PoV_NULL"]);
}

void Model::finishedSOMProcessing() {
    controller->povProccesingFinished();
}

bool Model::validGraphLoaded() {
    return graph != NULL && graph->numberOfNodes() > 0 && graph->numberOfEdges() > 0;
}

//Several operations
void Model::calculateRoles( string pov_name ) {
  string prop_name = pov_name;
  //prop_name.append("_Role");
  //IntegerProperty* role = graph->getLocalProperty<IntegerProperty>(prop_name);
    node n;
    forEach( n, graph->getNodes() ) {
        Role* node_role = new Role();
	Role* node_role1 = new Role();
        node_role->p_index = p_index(n,pov_name);
	node_role->z_index = z_index(n,pov_name);
	roles_information.insertData(n.id,pov_name,node_role);
	roles_information.getData(n.id,pov_name,node_role1);
	//cout << "(PoVName: " << pov_name.c_str() << ") Node " << n.id << " z_index = " << node_role.z_index << " P-index = " << node_role.p_index << endl;
	node_role1->print_role();
    }
}

float Model::z_index( node n, string pov_name ) {
    float result = 0;
    string pov_group = pov_name;
    string community_name = pov_name;
    pov_group.append("_Group");
    if ( graph->existLocalProperty(pov_group) ) {
      IntegerProperty* group = graph->getLocalProperty<IntegerProperty>(pov_group);
      int n_community = group->getNodeValue(n);
      char index[8];
      sprintf(index, "_%d", n_community );
      community_name.append(index);
      Graph* subg = graph->getSubGraph(community_name);
      if( subg != NULL ){
	float g_size = subg->numberOfNodes();
	float grp_avg_degree = 0;
	float grp_std_dev = 0;
	node inner_node;
	//The average
	forEach(inner_node,subg->getNodes() ){
	  grp_avg_degree += graph->deg(inner_node);//It's the overall degree of the node
	}
	grp_avg_degree /= g_size;
	//The starndard deviation
	forEach(inner_node,subg->getNodes() ){
	  grp_std_dev += (graph->deg(inner_node)-grp_avg_degree)*(graph->deg(inner_node)-grp_avg_degree);
	}
	grp_std_dev /= g_size;
	grp_std_dev = sqrt(grp_std_dev);
	//The inner degree
	node neighbor;
	float deg = 0;
        forEach( neighbor, graph->getInOutNodes(n) ) {
	  if( n_community == group->getNodeValue(neighbor) ){
	    deg++;
	  }
	}
	result = (deg-grp_avg_degree)/grp_std_dev;
      }
    }
    return result;
}

float Model::p_index( node n, string pov_name ) {
    float result = -1;
    pov_name.append("_Group");
    if ( graph->existLocalProperty(pov_name) ) {
        //Map containing the number of neighbors in other communities. The index is the community and the value is the number of links.
        map<int,float> outside_neighbors;
        //The property containing the community of the pov
        IntegerProperty* group = graph->getLocalProperty<IntegerProperty>(pov_name);
        //The community of the node n
        float node_deg = graph->deg(n);
        node neighbor;
        forEach( neighbor, graph->getInOutNodes(n) ) {
            int neighbor_community = group->getNodeValue(neighbor);
            if ( outside_neighbors.count(neighbor_community) > 0 ) {
                outside_neighbors[neighbor_community]++;
            } else {
                outside_neighbors[neighbor_community] = 1;
            }
        }
        result = 0;
        map<int,float>::iterator neighbors_iter;
        for ( neighbors_iter = outside_neighbors.begin(); neighbors_iter != outside_neighbors.end(); neighbors_iter++) {
            result += ((*neighbors_iter).second/node_deg)*((*neighbors_iter).second/node_deg);
        }
    }

    return 1-result;
}

int Model::getNumberOfSubGroups(string prefix) {
    int count = 0;
    Graph* subg;
    forEach( subg, graph->getSubGraphs() ) {
        if ( (int)subg->getName().find(prefix) != -1 ) {
            count ++;
        }
    }
    return count;
}

void Model::calculateCommunitiesComposition() {
    Iterator<string>* group = graph->getProperties();
    int index;
    while ( group->hasNext() ) {
        string name = group->next();
        if ( (index = name.find("_SOM_Group")) != -1 ) {
            IntegerProperty* prop = graph->getProperty<IntegerProperty>(name);
            string prefix = prop->getName().substr(0,index);
            Graph* subg;
            forEach( subg, graph->getSubGraphs() ) {
                if ( (int)subg->getName().find(prefix) != -1 ) {
                    map<int,int> comm_composition;
                    node n;
                    forEach(n,subg->getNodes()) {
                        int group_label = prop->getNodeValue(n);
                        if ( comm_composition.count(group_label) == 0 ) {
                            comm_composition[group_label] = 1;
                        } else {
                            comm_composition[group_label]++;
                        }
                        //cout << "From the model---- community " << subg->getName() << " node " << n.id << " category " << group_label << endl;
                    }
                    proportions[prefix].push_back(comm_composition);
                }
            }
        }
    }
    delete group;
}
