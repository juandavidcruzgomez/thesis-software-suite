/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Juan David Cruz Gomez <email>

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
