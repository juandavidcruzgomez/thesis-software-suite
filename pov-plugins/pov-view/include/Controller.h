/**
 The MIT License (MIT)

 Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne 
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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>

#include "Model.h"
#include "MainWidgetView.h"
#include "PoVConfigurationView.h"
#include "Role.h"

class PoVViewPlugin;
using namespace std;

class Controller{
public:
	Controller( MainWidgetView* _theView, Model* _theModel, PoVViewPlugin* _plugin );
	~Controller();
	
	//Events from the graph observer
	/**
	 * This message is sent by the grazph observer when a node or an edge is added or deleted from the graph.
	 */
	void graphChanged();
	//Events from the view//
	/**
	 * Receives the load action from the view.
	 */
	void loadFeaturesFile( string filename );
	/**
	 * Receives the configure pov action from the view.
	 */
	void configurePoVs();
	/**
	 * Recives the reset pov configuration action from the view.
	 */
	void resetPoVConfiguration();
	/**
	 * Receives the start process action from the view.
	 */
	void startProcess();
	/**
	 * Receives the step by step process action from the view.
	 */
	void stepByStepProcess();
	/**
	 * Receives the stop process action from the view.
	 */
	void stopProcess();
	/**
	 * Receives the hange action from the view
	 */
	void changeActiveLayoutAction( string povprefix );
	/**
	 * Receives a petition from the view for information about the proportions of the categories from the selected point of view in the null pov
	 * This message will be pased to the model. The model should know all the proportion, or how to calculate them
	 */
	void getCommunitiesInformation( string & selected_pov, vector< map<int,int> > & proportions);
	/**
	 * Ask the view to draw the roles graph of the selected point of view
	 */
	void drawRolesGraph( string pov_name, int where );
	/**
	 * The view ask for information 
	 */
	void getModEntropy( string pov_name, float& mod, float& ent );
	/**
	 * Will ask the model to change the layout of the graph according to the given point of view
	 */
	void distortLayout( string pov_name );
	//Events from the model//
	/**
	 * The controller is informed that the features have been loaded.
	 * @param info some information about the features.
	 */
	void featuresLoaded( string filename, int nb_features, vector<string> header );
	/**
	 * The model informs that the PoV property has been successfully created.
	 */
	void povPropertyCreated( int nb_pov );
	/**
	 * The controller is informed that the community detection process is finished.
	 */
	void communityDetectionFinished( int communities, double modularity );
	/**
	 * The controller is informed that the SOM is finished for all points of view.
	 */
	void povProccesingFinished();
	/**
	 * The controller is informed that the layout is finished.
	 */
	void layoutIsFinished();
	/**
	 * The controller is informed that the requested layout property does not exist.
	 */
	void layoutPropertyError( string povprefix );
	/**
	 * The model asks  to generate the thumbnails of the roles distribution using the pov names in the vector.
	 * Doing this the user can click in one thumbnail to activate it.
	 */
	void generateRolesThumbnails( vector<string> gen_pov_names );
	//FROM THE STARTER
	/**
	 * Ask the view to draw the degree distribution graph.
	 */
	void drawDegreeGraph();
private:
	//Mesages to the view//
	void updateFeaturesInformation( string filename, int nb_features, vector<string>& header );
	/**
	 * Ask the view to update the information about communities
	 */
	void updateCommunitiesInformation( int nb_communities, double modularity );
	
	//Messages to model//
	void loadFeatures( string filename );
	/**
	 * Ask the model to change the active layout
	 */
	void changeActiveLayout( string povprefix );
	/**
	 * Ask the model for the roles of a given pov
	 */
	void getRolesDistribution( std::map< int, Role* >& data, string pov_name );
	
private:
	
	Model* model;
	MainWidgetView* view;
	PoVConfigurationView* confView;
	
	PoVViewPlugin* plugin;
	
};


#endif

