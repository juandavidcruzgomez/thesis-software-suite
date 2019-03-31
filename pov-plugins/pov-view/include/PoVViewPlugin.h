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
#ifndef POVVIEWPLUGIN_H
#define POVVIEWPLUGIN_H

#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>
#include <tulip/Interactor.h>
#include <tulip/tulipconf.h>
#include <tulip/View.h>
#include <tulip/Graph.h>

#include <tulip/LayoutAlgorithm.h>

#include <string>

#include "information_definitions.h"

#include "MainWidgetView.h"
#include "Controller.h"
#include "Model.h"
#include "PoVGraphObserver.h"

using namespace std;
using namespace tlp;

class PoVViewPlugin	: public tlp::View
{
  Q_OBJECT
    
public:
	PoVViewPlugin();
	/**
	 * Construct the view
	 */
	QWidget* construct( QWidget* parent );
	/**
	 * Sets the data to the view
	 */
	void setData( tlp::Graph* graph, tlp::DataSet dataSet );
	/**
	 * Gets the data from the view
	 */
	void getData( tlp::Graph** graph, tlp::DataSet* dataSet );
	/**
	 * Returns the graph
	 */
	Graph *getGraph();
	/**
	 * Returns the widget
	 */
	QWidget* getWidget();
	
	void setInteractors(const std::list<tlp::Interactor *> &interactors);
	
	std::list<tlp::Interactor *> getInteractors();
	
	void setActiveInteractor(tlp::Interactor *interactor);
	
	tlp::Interactor *getActiveInteractor();
	
	void createPicture(const std::string &pictureName,int width=0, int height=0);
	
	bool addPointOfView( string name );
	string generateDefaultPovName();
	
	void activatePoVProperties();
	
	void updateLayout();
	
protected:
	//The graph and the data
	Graph *graph;
	DataSet* data;
	//The widget
	QWidget *view_widget;
	//The MVC components
	Controller* theController;
	MainWidgetView* theView;
	Model* theModel;
	
	//PoVGraphObserver observer;
	
public slots:
	void draw(){}
	void refresh() {}
	void init() {}
	void setGraph(tlp::Graph *graph) {
		this->graph=graph;
		draw();
	}
	
};

#endif
