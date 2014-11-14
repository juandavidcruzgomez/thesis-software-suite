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

#ifndef MAINWIDGETWINDOW_H
#define MAINWIDGETWINDOW_H

#include "ui_MainWidgetView.h"
#include <QFileDialog>
#include <string>

#include "qcustomplot.h"
#include "Role.h"

using namespace std;

class Controller;

class MainWidgetView : public QWidget, public Ui::mainWidgetView {
	Q_OBJECT
public:
	MainWidgetView( QWidget* parent = 0 );
	
	bool eventFilter(QObject *obj, QEvent *event);
	/**
	 * Sets the pointer to the controller.
	 */
	void setController( Controller* _controller );
	
	//Messages from the controller//
	/**
	 * 
	 * 
	 */
	void updateFeaturesView(string filename = "N/A", int nb_features = 0, vector<string> header = vector<string>(), int nb_pov = 0);
	/**
	 * Updates the value shown on the features summary
	 */
	void updateNBPoV( int nb_pov );
	/**
	 * Change the state of the execution buttons.
	 */
	void changeStateExecutionButtons(bool activate);
	/**
	 * Draws the degree distribution of the loaded graph from the given data.
	 */
	void drawGraphDegreeDistribution( map<int,int>& data );
	/**
	 * Draws the distribution of the roles from the given point of view.
	 */
	void drawRolesDistribution( map<int, Role*>& data, int target_graph );
	//Construction messages
	/**
	 * Updates the information about the graph
	 */
	void updateGraphInformation( int nodes, int edges );
	/**
	 * Update the information about the graph partition$
	 */
	void updateCommunitiesInformation( int communities, double modularity );
	/**
	 * Builds the tree view.
	 */
	void buildPovTreeView();
	/**
	 * Updates the tree view of the poins of view. Through the list the user can select the active point of view and change the view.
	 */
	void updatePovTree( map<int, vector<double> > properties );
	/**
	 * Disables the buttons for loading points of view on invalid graphs.
	 */
	void turnOffPoVButtons();
	/**
	 * Enables the buttons for loading points of view when a valid graph is loaded.
	 */
	void turnOnPoVButtons();
	/**
	 * Adds a thumbnail of the roles from the given pov
	 */
	void addRoleThumbnail( string pov_name );
public slots:
	/**
	 * Process the loadPovButton action
	 */
	void openFeaturesAction();
	/**
	 * Process the configurePovButton action.
	 */
	void configurePovAction();
	/**
	 * Process the resectConfigurationButton action.
	 */
	void resetConfigurationAction();
	/**
	 * Process the startButton action.
	 */
	void startProcessAction();
	/**
	 * Process the stepButton action.
	 */
	void stepProcessAction();
	/**
	 * Process the stopButton action.
	 */
	void stopProcessAction();
	/**
	 * If the user selects one point of view.
	 */
	void povTreeItemClicked(QTreeWidgetItem* item ,int column);
	/**
	 * If the user double clicks a point of view. For changing the layout
	 */
	void povTreeItemDoubleClicked(QTreeWidgetItem* item ,int column);
	/**
	 * Receives the contextual menu action over the roles graph
	 */
	void rolesGraphContextMenu(const QPoint& pos );
	
private:
	Controller* controller;
};

#endif
