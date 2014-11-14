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

#include "Controller.h"
#include <PoVViewPlugin.h>

Controller::Controller( MainWidgetView* _theView, Model* _theModel,PoVViewPlugin* _plugin ) {
    view = _theView;
    model = _theModel;
    confView = new PoVConfigurationView( NULL );
    plugin = _plugin;
}

Controller::~Controller() {}

//Events from the graph
void Controller::graphChanged() {
    view->updateGraphInformation(plugin->getGraph()->numberOfNodes(),plugin->getGraph()->numberOfEdges());
    if ( !model->validGraphLoaded() ) {
        view->turnOffPoVButtons();
    } else {
        view->turnOnPoVButtons();
	drawDegreeGraph();
    }
}

//Events from the view//
void Controller::loadFeaturesFile( string filename ) {
    //Pass the message to the model
    loadFeatures(filename);
}
void Controller::configurePoVs() {
    //Launch he configuration window
    int ret = confView->exec();
    if ( ret == QDialog::Accepted ) {
        //Activate the execution buttons
        view->changeStateExecutionButtons( true );
        //Inform the model and pass the povs configuration
        model->createGraphProperty(confView->getPovProperties() );
        //Tell the view to update the tree
        view->updatePovTree(confView->getPovProperties());
    }
}
void Controller::resetPoVConfiguration() {}
void Controller::startProcess() {
    model->executeAll();
}
void Controller::stepByStepProcess() {}
void Controller::stopProcess() {}

void Controller::changeActiveLayoutAction( string povprefix ) {
    changeActiveLayout(povprefix);
}

void Controller::getCommunitiesInformation( string& selected_pov, vector< std::map< int, int > >& proportions ){
  model->getACommunityComposition(selected_pov, proportions);
}
//Events from the model//
void Controller::featuresLoaded( string filename, int nb_features, vector<string> header ) {
    //Ask the view to update the information about the features.
    updateFeaturesInformation( filename, nb_features, header);
    confView->initializeForm(model->getLoader());
    configurePoVs();
}
void Controller::povPropertyCreated( int nb_pov ) {
    //Update the view
    view->updateNBPoV( nb_pov );
}
void Controller::communityDetectionFinished(int communities, double modularity) {
    updateCommunitiesInformation(communities,modularity);
    drawRolesGraph("PoV_NULL",1);
}
void Controller::povProccesingFinished() {

}
void Controller::layoutIsFinished() {
    plugin->updateLayout();
}

void Controller::layoutPropertyError(string povprefix ) {
    //So, ask the view to inform the user
    cout << "The layout property " << povprefix.c_str() << " does not exist." << endl;
}

void Controller::generateRolesThumbnails( vector<string> gen_pov_names ){
  for( int i = 0; i < (int)gen_pov_names.size(); i++ ){
    drawRolesGraph(gen_pov_names[i],2);
  }
}
//Mesages to the view//
void Controller::updateFeaturesInformation( string filename, int nb_features, vector<string>& header ) {
    view->updateFeaturesView(filename,nb_features,header);
}

void Controller::updateCommunitiesInformation( int nb_communities, double modularity ) {
    view->updateCommunitiesInformation(nb_communities,modularity);
}

void  Controller::drawRolesGraph( string pov_name, int where ){
  map<int, Role*> data;
  getRolesDistribution(data,pov_name);
  view->drawRolesDistribution(data,where);
}

void Controller::getModEntropy( string pov_name, float& mod, float& ent ){
  model->getModularityEntropy(pov_name,mod,ent);
}

void Controller::distortLayout( string pov_name ){
  model->performDistortion(pov_name);
}

void Controller::drawDegreeGraph(){
  map<int,int> data;
  model->calculateDegreeDistribution(data);
  view->drawGraphDegreeDistribution(data);
}
//Messages to model//
void Controller::loadFeatures( string filename ) {
    if ( model != NULL ) {
        model->loadFeaturesAction(filename);
    }
}

void Controller::changeActiveLayout( string povprefix ) {
    model->changeActiveLayout(povprefix);
}

void Controller::getRolesDistribution( map<int, Role*>& data, string pov_name ){
  model->getRolesFromPov( data, pov_name );
}
