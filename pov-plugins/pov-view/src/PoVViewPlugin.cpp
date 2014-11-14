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

#include "PoVViewPlugin.h"
#include <tulip/LayoutProperty.h>


// VIEWPLUGIN(ClassName, "ViewName", "Authors", "date", "Long view plugin name", "plugin_release");
VIEWPLUGIN(PoVViewPlugin, "PoVViewPlugin", "Juan David Cruz Gomez", "07/02/2012", "PoV View Plugin", "1.0");

PoVViewPlugin::PoVViewPlugin(){
	addDependency<Algorithm>("Community Detection Louvain", "1.0");
	addDependency<LayoutAlgorithm>("Boundary layout", "1.0");
	addDependency<Algorithm>("PoV clustering algorithm", "1.0");
}

/**
 * Construct the view
 */
QWidget* PoVViewPlugin::construct( QWidget* parent ){
	view_widget = new QWidget(parent);
	theView = new MainWidgetView(view_widget);
	view_widget->setMinimumSize(theView->minimumSize());
	view_widget->resize(theView->minimumSize());
	theModel = new Model();
	theController = new Controller( theView, theModel, this );
	theModel->setController(theController);
	theView->setController(theController);
	//observer.setController(theController);
	return view_widget;
}
/**
 * Sets the data to the view
 */
void PoVViewPlugin::setData( tlp::Graph* graph, tlp::DataSet dataSet ){
	this->graph = graph;
	//this->graph->addGraphObserver(&this->observer);
	data = &dataSet;
	theModel->setData(this->graph, *data);
	theView->updateGraphInformation(graph->numberOfNodes(),graph->numberOfEdges());
	if( !theModel->validGraphLoaded() ){
	  theView->turnOffPoVButtons();
	}
	theController->drawDegreeGraph();
	draw();
}
/**
 * Gets the data from the view
 */
void PoVViewPlugin::getData( tlp::Graph** graph, tlp::DataSet* dataSet ){
	*graph = this->graph;
	dataSet = data;
}
/**
 * Returns the graph
 */
Graph* PoVViewPlugin::getGraph(){
	return graph;
}

QWidget* PoVViewPlugin::getWidget() {
    return view_widget;
}

void PoVViewPlugin::setInteractors(const std::list<tlp::Interactor *> &interactors) {
}

std::list<tlp::Interactor *> PoVViewPlugin::getInteractors(){
	return std::list<tlp::Interactor *>();
}

void PoVViewPlugin::setActiveInteractor(tlp::Interactor *interactor) {
}

tlp::Interactor *PoVViewPlugin::getActiveInteractor() {
	return NULL;
}

void PoVViewPlugin::createPicture(const std::string &pictureName,int width, int height) {
}

bool PoVViewPlugin::addPointOfView( string name ){
	return false;
}

string PoVViewPlugin::generateDefaultPovName(){
	return string("");
}

void PoVViewPlugin::activatePoVProperties(){}

void PoVViewPlugin::updateLayout(){
  Observable::holdObservers();
  LayoutProperty* layout = graph->getLocalProperty<LayoutProperty>("PoV_NULL_viewLayout");
  *layout = *graph->getLocalProperty<LayoutProperty>("viewLayout");
  Observable::unholdObservers();
}
