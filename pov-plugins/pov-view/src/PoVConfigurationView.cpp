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


#include "PoVConfigurationView.h"

#include "SemanticPatternLoader.h"
#include <tulip/AbstractProperty.h>

PoVConfigurationView::PoVConfigurationView( QDialog* parent ) : QDialog(parent) {
    setupUi(this);
    actual_number = 0;
    connect(this->nbPoVSpinBox,SIGNAL(valueChanged(int)),this,SLOT(processSpinBoxEvent(int)));
    connect(this->povComboBox, SIGNAL(currentIndexChanged(int)), this,SLOT(onChangePointOfView(int)));
    connect(this->saveButton,SIGNAL(pressed()),this, SLOT(saveLimits()) );
    connect(this->povStartSpinBox,SIGNAL(valueChanged(int)),this,SLOT(highlightColumns()));
    connect(this->povEndSpinBox,SIGNAL(valueChanged(int)),this,SLOT(highlightColumns()));
    connect(this->buttonBox,SIGNAL(accepted()),this,SLOT(savePointsOfView()) );
    connect(this->buttonBox,SIGNAL(rejected()),this,SLOT(close()));
}

void PoVConfigurationView::initializeForm( SemanticPatternLoader* _semanticLoader ) {
	semanticLoader = _semanticLoader;
    this->povComboBox->setEnabled(false);
    //Set the limit of the limit spinboxes
    povStartSpinBox->setMinimum( 0 );
    povStartSpinBox->setMaximum( semanticLoader->getPatternSize() - 1 );
    povEndSpinBox->setMinimum( 0 );
    povEndSpinBox->setMaximum( semanticLoader->getPatternSize() - 1 );
    povStartSpinBox->setEnabled(false);
    povEndSpinBox->setEnabled(false);
	nbPatternsInfoLabel->setText( QString::number( semanticLoader->getPatterns().size() ) );
	nbFeaturesInfoLabel->setText( QString::number( semanticLoader->getPatternSize() ) );
    initializeTable();
}

void PoVConfigurationView::addPovToList( int number ) {
    QString povname("PoV");
    povname.append(QString::number(number,10));
    this->povComboBox->addItem( povname );
    actual_number = this->povComboBox->count();
    pov_configuration[number]=pair<int,int>(0,0);
}

void PoVConfigurationView::removePovFromList( int number ) {
    if ( actual_number < 1 ) {
        this->povComboBox->setEnabled(false);
        povStartSpinBox->setEnabled(false);
        povEndSpinBox->setEnabled(false);
    }
    QString povname("PoV");
    povname.append(QString::number(number,10));
    this->povComboBox->removeItem(actual_number-1);
    pov_configuration.erase(number);
    actual_number = this->povComboBox->count();
}

void PoVConfigurationView::onChangePointOfView( int index ) {
    pair<int,int> limits = pov_configuration[index];
    povStartSpinBox->setValue(limits.first);
    povEndSpinBox->setValue(limits.second);
}

void PoVConfigurationView::processSpinBoxEvent( int number ) {
    if ( number > actual_number ) {
        addPovToList( number );
        if ( actual_number > 0 ) {
            this->povComboBox->setEnabled(true);
            povStartSpinBox->setEnabled(true);
            povEndSpinBox->setEnabled(true);
	    highlightColumns();
        }
    } else if ( number < actual_number ) {
        removePovFromList( number );
    }
}

void PoVConfigurationView::saveLimits() {
    int povindex = povComboBox->currentIndex();
    int start = povStartSpinBox->value();
    int end = povEndSpinBox->value();
    pov_configuration[povindex]=pair<int,int>(start, end);
}

void PoVConfigurationView::highlightColumns() {
    int start = povStartSpinBox->value();
    int end = povEndSpinBox->value();
    int rows = patternTable->rowCount();
    int cols = patternTable->columnCount();
    for ( int i = 0; i < rows; i++ ) {
        for ( int j = 0; j < cols; j++ ) {
            if ( j >= start && j <= end ) {
                patternTable->item(i,j)->setBackgroundColor(QColor(0,0,255,128));
            } else {
                patternTable->item(i,j)->setBackgroundColor(QColor(255,255,255));
            }
        }
    }
}

void PoVConfigurationView::initializeTable() {
    int i,j;
    vector<string> labels = semanticLoader->getHeaderLabels();
    map<int, vector<float> > patterns = semanticLoader->getPatterns();
    patternTable->setRowCount(patterns.size());
    patternTable->setColumnCount((int)labels.size());
    QString header;
    for ( i = 0; i < (int)labels.size(); i++ ) {
        header.append(labels[i].c_str());
        if ( i < (int)labels.size() - 1 ) {
            header.append(";");
        }
    }
    patternTable->setHorizontalHeaderLabels(header.split(";"));
    for ( i = 0; i < (int)patterns.size(); i++ ) {
        for ( j = 0; j < (int)labels.size(); j++ ) {
            patternTable->setItem(i,j,new QTableWidgetItem(QString::number(patterns[i][j])));
        }
    }
}

void PoVConfigurationView::changeStatusMessage( int event ){
  QString message( "" );
  switch( event ){
    case( READY ):
      message.append("Ready.");
      break;
    case( START_GREATER ):
      message.append("The start index of the point of view is lower than the end index.");
      break;
    case( NO_POVS ):
      message.append("There are no defined points of view.");
      break;
    default:
      break;
  }
  statusReportLabel->setText(message);
}

void PoVConfigurationView::addProperty( int index, vector<double> features ){
  povproperties[index] = features;
}

map<int,vector<double> > PoVConfigurationView::getPovProperties() const{
  return povproperties;
}

void PoVConfigurationView::savePointsOfView(){
	//Points of view accepted//
  //Save the patterns to a map of patterns
  int i,j;
  int rows = patternTable->rowCount();
  int cols = patternTable->columnCount();
  vector<double>pointsOfView;
  for( i = 0; i < rows; i++ ){
    pointsOfView.push_back((int)povComboBox->count());
    map<int, pair<int, int> >::iterator iter;
    for( j = 0; j < (int)pov_configuration.size()-1; j++ ){
      pointsOfView.push_back(pov_configuration[j].first);
      pointsOfView.push_back(pov_configuration[j].second);
    }
    for( j = 0; j < cols; j++ ){
      pointsOfView.push_back( patternTable->item(i,j)->text().toDouble());
    }
    addProperty( i, pointsOfView );
    pointsOfView.clear();
  }
  close();
}
