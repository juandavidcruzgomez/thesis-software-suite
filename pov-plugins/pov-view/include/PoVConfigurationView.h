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
