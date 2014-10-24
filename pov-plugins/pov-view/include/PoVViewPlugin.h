/*
 <one line to give the program's name and a brief idea of what it does.>
 Copyright (C) 2012  <copyright holder> <email>
 
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
