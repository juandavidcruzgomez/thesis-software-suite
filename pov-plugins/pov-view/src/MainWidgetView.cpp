/*
 *  MainWidgetView.cpp
 *  PoVIntegratorViewPlugin
 *
 *  Created by Juan David CRUZ GOMEZ on 6/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainWidgetView.h"
#include "PoVViewPlugin.h"
#include "Controller.h"
#include <qmenu.h>

MainWidgetView::MainWidgetView( QWidget* parent ) : QWidget(parent) {
    setupUi(this);
    controller = NULL;
    buildPovTreeView();
    //Plug the buttons to actions
    connect(loadPovButton, SIGNAL(clicked()), this, SLOT(openFeaturesAction()));
    connect(configurePoVButton, SIGNAL(clicked()), this, SLOT(configurePovAction()));
    connect(configurePoVButton, SIGNAL(clicked()), this, SLOT(configurePovAction()));
    connect(resetConfigurationButton, SIGNAL(clicked()), this, SLOT(resetConfigurationAction()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startProcessAction()));
    connect(stepButton, SIGNAL(clicked()), this, SLOT(stepProcessAction()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopProcessAction()));
    connect(povTreeList, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(povTreeItemClicked(QTreeWidgetItem*,int)));
    connect(povTreeList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(povTreeItemDoubleClicked(QTreeWidgetItem*,int)));
    //Context menus interactions
    pov1RolesDistW->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pov1RolesDistW, SIGNAL(customContextMenuRequested(QPoint&)),this,SLOT(rolesGraphContextMenu(QPoint&)));
    
    //Initialize all the graph plots
    degreeDistSpaceW->xAxis->setRange(0,1);
    degreeDistSpaceW->yAxis->setRange(0,1);
    degreeDistSpaceW->xAxis->setLabel("Degree");
    degreeDistSpaceW->yAxis->setLabel("Frequency");
    barGraphSpacePoVNull->xAxis->setRange(0,1);
    barGraphSpacePoVNull->xAxis->setLabel("Communities");
    barGraphSpacePoVNull->yAxis->setRange(0,1);
    barGraphSpacePoVNull->yAxis->setLabel("Categories count");
    barGraphSpacePoVSel->xAxis->setRange(0,1);
    barGraphSpacePoVSel->xAxis->setLabel("Communities");
    barGraphSpacePoVSel->yAxis->setRange(0,1);
    barGraphSpacePoVSel->yAxis->setLabel("Categories count");
    pov1RolesDistW->xAxis->setRange(0,1);
    pov1RolesDistW->xAxis->setLabel("P index");
    pov1RolesDistW->yAxis->setRange(0,1);
    pov1RolesDistW->yAxis->setLabel("z index");
    pov2RolesDistW->xAxis->setRange(0,1);
    pov2RolesDistW->xAxis->setLabel("P index");
    pov2RolesDistW->yAxis->setRange(0,1);
    pov2RolesDistW->yAxis->setLabel("z index");
    //Initialize the thumbnail area
    QLayout* roleArea = new QGridLayout(roleThumbnailArea);
    roleThumbnailArea->setLayout(roleArea);

}

bool MainWidgetView::eventFilter(QObject *obj, QEvent *event) {
    return true;
}

void MainWidgetView::setController( Controller* _controller ) {
    controller = _controller;
}

void MainWidgetView::openFeaturesAction() {
    QString filename = QFileDialog::getOpenFileName(this, "Features file selection", ".", "Features files(*.txt)" );
    if ( controller != NULL && filename!="") {
        controller->loadFeaturesFile( filename.toStdString());
    }
}

void MainWidgetView::configurePovAction() {
    if ( controller != NULL ) {
        controller->configurePoVs();
    }
}

void MainWidgetView::resetConfigurationAction() {
    if ( controller != NULL ) {
        controller->resetPoVConfiguration();
    }
}

void MainWidgetView::startProcessAction() {
    if ( controller != NULL ) {
        controller->startProcess();
    }
}

void MainWidgetView::stepProcessAction() {
    if ( controller != NULL ) {
        controller->stepByStepProcess();
    }
}

void MainWidgetView::stopProcessAction() {
    if ( controller != NULL ) {
        controller->stopProcess();
    }
}
void MainWidgetView::povTreeItemClicked(QTreeWidgetItem* item ,int column) {
    //Show information about the point of view...
    cout << "Item clicked. Value: " << item->text(0).toStdString().c_str() << ". It has " << item->text(1).toStdString().c_str() << " features." << endl;
    //Update the bar diagrams and the information
    string selected_pov = item->text(0).toStdString();
    float mod = 0;
    float ent = 1;
    controller->getModEntropy(selected_pov,mod,ent);
    povSelModValue->setNum(mod);
    povSelEntropyValue->setNum(ent);
    int target = (int)selected_pov.find("PoV_NULL") != -1 ? 1 : 2;
    controller->drawRolesGraph(selected_pov, target);
//     string suffix = "_SOM_Group";
//     vector<map<int,int> > distribution;
//     controller->getCommunitiesInformation(selected_pov,distribution);
//     QVector<double> ticks;
//     QVector<QString> labels;
//     QString cat = "Category ";
//     for ( int i = 0; i < distribution.size(); i++ ) {
//         ticks << i;
//         labels << cat.append(i);
//         map<int,int> group = distribution[i];
//         map<int,int>::iterator iter;
// //       cout << "Community " << i << endl;
// //       for( iter = group.begin(); iter != group.end(); iter++ ){
// // 	cout << "\t\t\t\tCategory " << (*iter).first << " has " << (*iter).second << " elements\n";
// //       }
//         int max_comm = item->text(1).toInt();
//         barGraphSpacePoVSel->xAxis->setRange(0,max_comm);
//         //QCPBars *regen = new QCPBars(customPlot->xAxis, customPlot->yAxis);
//         //A vector containing the bars to be plotted
//         vector<QCPBars *> categories;
//         int j = 0;
//         for ( iter = group.begin(); iter != group.end(); iter++ ) {
//             categories.push_back(new QCPBars(barGraphSpacePoVSel->xAxis, barGraphSpacePoVSel->yAxis));
//             barGraphSpacePoVSel->addPlottable(categories[i]);
//             //Colors and shit
// 
//             //The data
// 
//             j++;
//         }
//         //Prepare x axis
// 
// //   ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
// //   labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
// //   customPlot->xAxis->setAutoTicks(false);
// //   customPlot->xAxis->setAutoTickLabels(false);
// //   customPlot->xAxis->setTickVector(ticks);
// //   customPlot->xAxis->setTickVectorLabels(labels);
// //   customPlot->xAxis->setTickLabelRotation(60);
// //   customPlot->xAxis->setSubTickCount(0);
// //   customPlot->xAxis->setTickLength(0, 4);
// //   customPlot->xAxis->setGrid(false);
// //   customPlot->xAxis->setRange(0, 8);
//     }

    //First, calculate the composition of the null pov

}

void MainWidgetView::povTreeItemDoubleClicked(QTreeWidgetItem* item ,int column) {
    //Change the layout... yeah
    string povname = item->text(0).toStdString();
    //So, ask the controller...
    //controller->changeActiveLayoutAction(povname);
    controller->distortLayout(povname);
}

void MainWidgetView::rolesGraphContextMenu(const QPoint& pos ){
  QPoint globalPos = pov1RolesDistW->mapToGlobal(pos);
  QMenu menu;
  menu.addAction("Save to PDF" );
  
  QAction* selectedItem = menu.exec(globalPos);
    if (selectedItem)
    {
        cout << "Save to pdf..." << endl;
    }
    else
    {
        cout << "GTFO" << endl;
    }
}

//Messages from the controller//
void MainWidgetView::updateFeaturesView(string filename, int nb_features, vector<string> header, int nb_pov ) {
    featuresFileNameInfo->setText(QString(filename.c_str()));
    nbFeaturesInfo->setText(QString::number(nb_features, 10));
    nbPoVInfo->setText(QString::number(nb_pov, 10));
    for ( int i = 0; i < (int)header.size(); i++ ) {
        povHeaderList->addItem(QString(header[i].c_str()));
    }
}

void MainWidgetView::updateNBPoV( int nb_pov ) {
    nbPoVInfo->setText(QString::number(nb_pov, 10));
}

void MainWidgetView::changeStateExecutionButtons(bool activate) {
    startButton->setEnabled(activate);
    stepButton->setEnabled(activate);
    stopButton->setEnabled(activate);
}

void MainWidgetView::drawGraphDegreeDistribution( std::map< int, int >& data ) {
    QVector<double> degrees;
    QVector<double> freq;
    map<int,int>::iterator iter;
    double deg_max = 0;
    double fr_max = 0;
    for ( iter = data.begin(); iter != data.end(); iter++ ) {
        double deg = (*iter).first;
        double fr =  (*iter).second;
        if ( deg > deg_max ) {
            deg_max = deg;
        }
        if ( fr > fr_max ) {
            fr_max = fr;
        }
        //cout << deg << "->" << fr << endl;
        degrees.push_back(deg);
        freq.push_back(fr);
    }

    degreeDistSpaceW->addGraph();
    degreeDistSpaceW->graph(0)->setData( degrees, freq);
    degreeDistSpaceW->xAxis->setLabel("Degree");
    degreeDistSpaceW->yAxis->setLabel("Frequency");
    degreeDistSpaceW->xAxis->setRange(0,deg_max);
    degreeDistSpaceW->yAxis->setRange(0,fr_max);
    degreeDistSpaceW->replot();
}

void MainWidgetView::drawRolesDistribution( std::map< int, Role* >& data, int target_graph ) {
    QCustomPlot* target = target_graph == 1 ? pov1RolesDistW : pov2RolesDistW;
    target->clearGraphs();
    target->legend->setVisible(true);
    target->legend->setFont(QFont("Helvetica", 8));
    target->legend->setMargin(1,1,1,1);
    target->legend->setPositionStyle(QCPLegend::psTopRight);
    target->legend->setPadding(0,0,0,0);
    QVector<double> p_index;
    QVector<double> z_index;
    QStringList rolesNames;
    map<int,Role*>::iterator iter;
    map<int,vector<pair<float,float> > > roles_per_type;
    double p_max = 0;
    double z_max = 0;
    double z_min = 10000;
    for ( iter = data.begin(); iter != data.end(); iter++ ) {
        if ( (*iter).second != NULL ) {
            double p = (*iter).second->p_index;
            double z =  (*iter).second->z_index;
            int role = (*iter).second->role();
            if ( p > p_max ) {
                p_max = p;
            }
            if ( z > z_max ) {
                z_max = z;
            }
            if ( z < z_min ) {
                z_min = z;
            }
            roles_per_type[role].push_back(pair<float,float>(p,z));
        }
    }
    target->xAxis->setRange(0,1.2);
    target->yAxis->setRange(z_min-0.2,z_max+0.2);
    map<int,vector<pair<float,float> > >::iterator roles_iter;
    QPen pen;
    for ( roles_iter = roles_per_type.begin(); roles_iter != roles_per_type.end(); roles_iter++ ) {
        target->addGraph();
        QString role_name("Role ");
        int role = (*roles_iter).first;
        role_name.append(QString::number(role));
        float pi = 3.141592;
        float step = 2.0*pi/14.0;
        pen.setColor(QColor(abs(cos((role-1)*2*step))*255, abs(cos(((role-1)*2*step)+pi/2.0))*255, abs(cos(((role-1)*2*step)+3*pi/2.0))*255));
        target->graph()->setPen(pen);
        target->graph()->setLineStyle(QCPGraph::lsNone);
        target->graph()->setScatterSize(5);
        target->graph()->setName(role_name);
        target->graph()->setScatterStyle((QCP::ScatterStyle)(role+1));
        vector<pair<float, float> > coords = (*roles_iter).second;
        for ( int i = 0; i < (int)coords.size(); i++ ) {
            float x = coords[i].first;
            float y = coords[i].second;
            target->graph()->addData(x,y);
        }
    }
    target->replot();
    target->savePdf("/home/juancrug/pepe.pdf");
}

//Construction messages
void MainWidgetView::updateGraphInformation( int nodes, int edges ) {
    nbNodesInfo->setNum(nodes);
    nbEdgesInfo->setNum(edges);
}

void MainWidgetView::updateCommunitiesInformation( int communities, double modularity ) {
    nbCommunitiesInfo->setNum(communities);
    barGraphSpacePoVNull->xAxis->setRange(0,communities);
    modularityInfo->setNum(modularity);
    povNullModValue->setNum(modularity);
}

void MainWidgetView::buildPovTreeView() {
    povTreeList->setColumnCount(2);
    QStringList header;
    header << "PoV Name" << "Number of features";
    povTreeList->setHeaderLabels(header);
}

void MainWidgetView::updatePovTree( std::map< int, std::vector< double > > properties ) {
    int nb_pov = properties[0][0];
    int counter = 1;
    QList<QTreeWidgetItem *> items;
    cout << "Names size: " << properties.size() << endl;
    for (int i = -1; i < nb_pov; ++i) {
        QStringList item;
        QString name = "PoV_";
        if ( i == -1 ) {
            name.append( "NULL" );
            item << name << "--";
        } else {
            name.append(QString::number(i,10));
            int features = 0;
            features = properties[0][counter+1]-properties[0][counter]+1;
            counter += 2;
            item << name << QString::number(features);
        }

        cout << "Name: " << name.toStdString().c_str() << endl;
        items.append(new QTreeWidgetItem((QTreeWidget*)0, item ) );
    }
    povTreeList->insertTopLevelItems(0, items);
}

void MainWidgetView::turnOffPoVButtons() {
    loadPovButton->setEnabled(false);
    configurePoVButton->setEnabled(false);
    resetConfigurationButton->setEnabled(false);
}

void MainWidgetView::turnOnPoVButtons() {
    loadPovButton->setEnabled(true);
    configurePoVButton->setEnabled(true);
    resetConfigurationButton->setEnabled(true);
}

void MainWidgetView::addRoleThumbnail( string pov_name ){
  QWidget* thumbnail = new QWidget();
  thumbnail->setMinimumSize(128,64);
  thumbnail->setMaximumSize(128,64);
  QGridLayout* roleArea = (QGridLayout*)roleThumbnailArea->layout();
  roleArea->addWidget(thumbnail);
}
