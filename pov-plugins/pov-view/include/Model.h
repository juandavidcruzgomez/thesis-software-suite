/*
 *  Model.h
 *  PoVIntegratorViewPlugin
 *
 *  Created by Juan David CRUZ GOMEZ on 6/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <tulip/Graph.h>
#include <tulip/IntegerProperty.h>
#include "information_definitions.h"
#include "SemanticPatternLoader.h"
#include "GeneralPoVInfoContainer.h"
#include "Role.h"
#include "PoVLayoutDistortion.h"

#include <iostream>

using namespace std;
using namespace tlp;

class Controller;


class Model{
  friend class PoVLayoutDistortion;
public:
    Model();

    /**
     * Sets the pointer to the controller.
     */
    void setController( Controller* _controller );
    /**
     * Sets the data for the model.
     */
    void setData( Graph* _graph, DataSet _data );

    SemanticPatternLoader* getLoader() const;

    //Messages from the controller//
    /**
     * The controller asks the model to load the features from the file.
     */
    void loadFeaturesAction( string filename );
    /**
     * The controller asks the model to create the PoV property on the graph and set each node withits respective value
     */
    void createGraphProperty( map<int, vector<double> > properties );
    /**
     * Executes communityDetection step.
     */
    void executeCommunityDetection();
    /**
     * Executes the data clustering step.
     */
    void executeDataClustering();
    /**
     * Executes the index generation for the partitions. These indeces include ARI and CA
     */
    void executeIndicesGeneration();
    /**
     * Produces the layouts for each point of view.
     */
    void executeLayouts();
    /**
     * Measures the distances between layouts.
     */
    void measureLayouts();
    /**
     * Executes the whole process. Cannot be stopped.
     */
    void executeAll();
    /**
     *
     */
    void changeActiveLayout( string povprefix );
    /**
     * Calculates the degree distribution of the loaded graph.
     */
    void calculateDegreeDistribution( std::map< int, int >& data );
    /**
     * Gets the data about the community composition for a given point of view
     */
    void getACommunityComposition( string pov_name, vector<map<int,int> >& data );
    /**
     * The controller ask for this information
     */
    void getModularityEntropy( string pov_name, float& modularity, float& entropy );
    /**
     * Returns the roles of theno de for a given point of view
     */
    void getRolesFromPov( std::map< int, Role* >& data, string pov_name );
    /**
     * Execute the distortion of the layout according to the given pov
     */
    void performDistortion( string pov_name );
    //Messages to the controller//
    /**
     * Tells the controller that the features were loaded.
     */
    void finishedFeaturesLoad( string &filename );
    /**
     * Tells the controller that the community detection process has finished
     */
    void finishedCommunityDetection();
    /**
     * Tell the controller that the som training has finished for all PoV
     */
    void finishedSOMProcessing();
    /**
     * Tells the controller if there is a valid loaded graph.
     */
    bool validGraphLoaded();

    //Several model operations
    /**
     * Calculates the roles for the designed point of view.
     */
    void calculateRoles(string pov_name);
    /**
     * Returns the number of groups of a specific prefix
     */
    int getNumberOfSubGroups(string prefix);
    /**
     * This method will calculate the number of nodes with some feature in each community.
     */
    void calculateCommunitiesComposition();
    
private:
  /**
   * Calculates the z_index of the node n in teh given pov
   */
  float z_index( node n, string pov_name );
  /**
   * Calculates the participation index of the node n in the given pov
   */
  float p_index( node n, string pov_name );

private:
    /**
     * A pinter to the controller
     */
    Controller* controller;
    /**
     * A pointer to the graph
     */
    Graph* graph;
    /**
     * A reference to the data set
     */
    DataSet data;
    /**
     * A pointer to the semantic information loader
     */
    SemanticPatternLoader* loader;
    /**
     * The number of points of view
     */
    int nb_pov;
    /**
     * A map containing the number of communities in each point of view
     */
    map<string,int> nb_communities;
    /**
     * A map containing the modularity value for each point of view
     */
    map<string,double> modularities;
    /**
     * A map containing the entropy value for each point of view
     */
    map<string,double> entropies;
    /**
     * A map containing the proportion of categories for each community. The x size of the vector is the number of communities, the y size is
     * the number of each category in teh community.
     */
    map<string,vector<map<int,int> > > proportions;
    /**
     * The structure containing the role of each node in each point of view.
     */
    GeneralPoVInfoContainer<Role*> roles_information;
};

#endif

