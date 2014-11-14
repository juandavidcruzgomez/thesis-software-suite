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
