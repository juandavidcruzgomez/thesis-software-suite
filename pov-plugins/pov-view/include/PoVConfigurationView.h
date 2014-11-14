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


#ifndef POVCONFIGURATIONVIEW_H
#define POVCONFIGURATIONVIEW_H

#define READY 0
#define START_GREATER 1
#define NO_POVS 2


#include <tulip/Graph.h>
#include <tulip/DoubleProperty.h>

#include <QtGui/QDialog>

#include <map>

#include "ui_PatternLoadWindow.h"



using namespace std;
using namespace tlp;

class SemanticPatternLoader;

class PoVConfigurationView :public QDialog, public Ui::PatternLoadWindow {
  Q_OBJECT
public:
  PoVConfigurationView( QDialog* parent );
  /**
   * Sets all elements in the form
   */
  void initializeForm( SemanticPatternLoader* _semanticLoader );
  
  /**
   * Adds a new point of view to the list
   */
  void addPovToList( int number );
  /**
   * Remones the last point of view from the list
   */
  void removePovFromList( int number );
  
  void initializeTable();
  
  void changeStatusMessage( int event );
  
  void addProperty( int index, vector<double> features );
  
  map<int,vector<double> > getPovProperties() const;
	
public slots:
  void processSpinBoxEvent( int number );
  
  void onChangePointOfView( int index );
  
  void saveLimits();
  
  void highlightColumns();
  
  void savePointsOfView();
  
private:
  int actual_number;
  SemanticPatternLoader* semanticLoader;
  map<int, pair< int,int> > pov_configuration;
  map<int,vector<double> > povproperties;
};

#endif // POVCONFIGURATIONVIEW_H
