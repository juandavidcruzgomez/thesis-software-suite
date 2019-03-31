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

#include "CLayoutSpace.h"

//The static strings
string CLayoutSpace::DIS_MAT_GENERATION_TIME = "DIS_MAT_GENERATION_TIME";
    
string CLayoutSpace::BORDER_NODES_CALC_TIME = "BORDER_NODES_CALC_TIME";
    
string CLayoutSpace::INNER_NODES_CALC_TIME_ = "INNER_NODES_CALC_TIME_";
    
string CLayoutSpace::DELTA_VAR_PER_SET_ = "DELTA_VAR_PER_SET_";

CLayoutSpace::CLayoutSpace() {
    n_threads = 0;
    totalBorder = 0;
    totalInner = 0;
    proportions = NULL;
    innerNodesSize = NULL;
    logger = NULL;
}

CLayoutSpace::CLayoutSpace(tlp::Graph * &_theGraph) {
    theGraph = _theGraph;
    proportions = NULL;
    innerNodesSize = NULL;
    if (theGraph != NULL) {
        max_innerNodes = 0;
        tlp::Iterator<tlp::Graph*> *subIter = theGraph->getSubGraphs();
        n_threads = 1;
        while (subIter->hasNext()) {
            n_threads++;
            subIter->next();
        }
        delete subIter;
        totalBorder = 0;
        totalInner = 0;
    }
    logger = new ExecutionLog();
    //Here we create the time events
    logger->create_event(DIS_MAT_GENERATION_TIME, TIME_LOG );
    logger->create_event(BORDER_NODES_CALC_TIME, TIME_LOG );
    //The time event for each inner tlp::node set will be created during the difinition of the set
}

CLayoutSpace::~CLayoutSpace() {
    if (proportions != NULL) {
        delete[] proportions;
        proportions = NULL;
    }
    if( innerNodesSize != NULL ){
	delete[] innerNodesSize;
	innerNodesSize = NULL;
    }
}

void CLayoutSpace::initialize(){
  //Debug msgs
  std::cout << "Initializing the algorithm... " << std::endl;
  if( ( proportions = new double[n_threads - 1] ) != 0 ){
    std::cout << "\tProportion array created: " << ((n_threads - 1)*sizeof(double)/(1024.0*1024.0)) << " Mb. " << std::endl;
  }
  if( ( innerNodesSize = new float[n_threads - 1] ) != 0 ){
    std::cout << "\tInner ndoes size array created: " << ((n_threads - 1)*sizeof(float)/(1024.0*1024.0)) << " Mb. " << std::endl;
  }
  std::cout << "Done initializing the algorithm." << std::endl;
}

void CLayoutSpace::startAlgorithm() {
    initialize();
    processGrahp();
    //Now, set the appropiate coordinates for the points
    calculatePositionByBorderNodes();
    logger->print_events();
}

void CLayoutSpace::processGrahp() {
    //Debug msgs
    std::cout << "Starting processing the graph... " << std::endl;
    int innerCount = 0;
    int i = 0;
    m_nmax_points = 0;
    std::vector<std::vector<tlp::node> > temporal_innernodes_storage;
    tlp::Iterator<tlp::Graph*> *subIter = theGraph->getSubGraphs();
    while (subIter->hasNext()) {
        tlp::Graph* actualGroup = subIter->next();
        vector<tlp::node> _innerNodes = divideNodesByType(actualGroup, i);
        innerCount += _innerNodes.size();
        if ( (int)_innerNodes.size() > m_nmax_points ) {
            m_nmax_points = _innerNodes.size();
        }
        if (_innerNodes.size() > 0) {
            innerNodesSize[i] = (float)_innerNodes.size();
        } else {
            proportions[i] = 0.0;
        }
        temporal_innernodes_storage.push_back(_innerNodes);
        i++;
    }
    delete subIter;
    if ( (int)this->borderNodes.size() > m_nmax_points ) {
        m_nmax_points = this->borderNodes.size();
    }
    std::cout << "\tCreating the working spaces: " << std::endl;
    //Initialize the working spaces :)
    if( ( dissmat = new Matrix(m_nmax_points,m_nmax_points,COLUMN_MAJOR) ) != 0 ){
      std::cout << "\t\tCreated dissimilarity matrix of " << m_nmax_points << "x" << m_nmax_points << " and " << dissmat->getSize()/(1024.0*1024.0) << " Mb. " << std::endl;
    }
    std::cout << "\t\t\tCreating the MDS space: " << std::endl;
    if( ( mdsspace = new MDS_space(m_nmax_points, dissmat, EUCLIDEAN) ) != 0 ){
	std::cout << "\t\t\tCreated MDS space. " << mdsspace->getSize()/(1024.0*1024.0) << "Mb used." << std::endl;
    }
    //Now, everything is recyclage...
    //Start with the border nodes
    processBorderNodeSet();
    //Now the inner nodes
    for (i = 0; i < (int)temporal_innernodes_storage.size(); i++ ) {
        processNextInnerGroup(temporal_innernodes_storage[i]);
    }
    //Now, you can delete the spaces...
    delete dissmat;
    delete mdsspace;
    for (i = 0; i < (int)temporal_innernodes_storage.size(); i++ ) {
        temporal_innernodes_storage[i].clear();
    }
    temporal_innernodes_storage.clear();
}

void CLayoutSpace::processBorderNodeSet() {
  //Debug msgs
  cout << "Processing border nodes set: ";
    int i;
    int iter = 250;
    float delta = 1E-5;
    totalBorder = borderNodes.size();
    dissmat->recycleMatrixSpace(totalBorder, totalBorder);
    std::cout << totalBorder << " border nodes." << std::endl;
    clock_t init_time = clock();
    std::cout << "Calculating the graph dissimilarity matrix... " << std::endl;
    graphDissmilarityMatrix(this->borderNodes, theGraph, &jaccardDistance2, dissmat->getPdmatrix());
    //logger->create_event(DIS_MAT_GENERATION_TIME, TIME_LOG );
	float total_time = ((float)clock() - init_time)/CLOCKS_PER_SEC;
	std::cout << DIS_MAT_GENERATION_TIME << " " << total_time << std::endl;
	//TODO: fix the cast
    //logger->log_event(DIS_MAT_GENERATION_TIME, static_cast<void*>( &(float*)total_time ) );
    //Recycle!
    mdsspace->recycle_mds_space(totalBorder);
    mdsspace->calculate_initial_points();
    mdsspace->start_mds(iter, delta);
    Matrix* points = mdsspace->get_z_matrix();
    double x, y;
    double max_x = -100000;
    double max_y = -100000;
    double avg_x = 0;
    double avg_y = 0;
    std::vector<double> _x;
    std::vector<double> _y;
    for (i = 0; i < (int)borderNodes.size(); i++) {
        x = points->getElement(i, 0);
        y = points->getElement(i, 1);
        avg_x += x;
        avg_y += y;
        _x.push_back(x);
        _y.push_back(y);
    }
    avg_x /= (double)borderNodes.size();
    avg_y /= (double)borderNodes.size();
    for ( i = 0; i < (int)_x.size(); i++ ) {
        _x[i] -= avg_x;
        if ( abs(_x[i]) > max_x ) {
            max_x = abs(_x[i]);
        }
        _y[i] -= avg_y;
        if ( abs(_y[i]) > max_y ) {
            max_y = abs(_y[i]);
        }
    }
    for ( i = 0; i < (int)_x.size(); i++ ) {
        x = _x[i]/max_x;
        y = _y[i]/max_y;
        positions[borderNodes[i]] = tlp::Coord(x, y, 0);
    }
    std::cout << "Finishing processing border nodes." << std::endl;
    //NO, we don't delete here... we are recycling!
}

void CLayoutSpace::processNextInnerGroup( std::vector<tlp::node> _innerNodes ) {
  //Debug msgs
  std::cout << "Processing inner nodes set of size: ";
    int i;
    int iter = 250;
    float delta = 1E-5;
    int groupSize = _innerNodes.size();
    std::cout << groupSize << " nodes." << std::endl;
    if ( groupSize > 0 ) {
        dissmat->recycleMatrixSpace(groupSize, groupSize);
        graphDissmilarityMatrix(_innerNodes, theGraph, &jaccardDistance2, dissmat->getPdmatrix());
        mdsspace->recycle_mds_space(groupSize);
        mdsspace->calculate_initial_points();
        mdsspace->start_mds(iter, delta);
        Matrix* points = mdsspace->get_z_matrix();
        for ( i = 0; i < (int)_innerNodes.size(); i++ ) {
            positions[_innerNodes[i]] = tlp::Coord(points->getElement(i,0), points->getElement(i,1), 0);
        }
    }
    std::cout << "Finishing processing inner nodes." << std::endl;
}

void CLayoutSpace::calculatePositionByBorderNodes() {
    int j;
    int size = 0;
    double x = 0;
    double y = 0;
    int group = -1;
    double movement_x = 0;
    double movement_y = 0;
    double** averagePos = new double*[n_threads - 1];
    //The position of  the border nodes:
    size = n_threads - 1;
    for (j = 0; j < size; j++) {
        //x,y,count
        averagePos[j] = new double[3];
        averagePos[j][0] = 0;
        averagePos[j][1] = 0;
        averagePos[j][2] = 0;
    }
    size = borderNodes.size();
    for (j = 0; j < size; j++) {
        tlp::node n = borderNodes[j];
        tlp::Coord c = positions[n];
        x = c.getX() / 2.0;
        y = c.getY() / 2.0;
        positions[n] = tlp::Coord( x, y, 0 );
        int id = n.id;
        group = groupAssignation[id];
        averagePos[group][0] += x;
        averagePos[group][1] += y;
        averagePos[group][2]++;
    }
    tlp::Iterator<tlp::node>* nodeIter = theGraph->getNodes();
    while (nodeIter->hasNext()) {
        tlp::node n = nodeIter->next();
        int node_group = groupAssignation[n.id];
	if (node_type[n] == INNER_NODE) {
            double _size = averagePos[node_group][2] == 0 ? 1.0 : averagePos[node_group][2];
            double _x = averagePos[node_group][0] / _size;
            double _y = averagePos[node_group][1] / _size;
            double m = 0;
            if (_x != 0) {
                m = _y / _x;
                movement_x = sqrt(1 / ((m * m) + 1));
                movement_x *= _x < 0 ? -0.75 : 0.75;
                movement_y = m * movement_x;
            } else {
                movement_x = 0;
                movement_y = _y < 0 ? -0.75 : 0.75;
            }
            float size = 0.25 * (innerNodesSize[node_group] / max_innerNodes);
            x = positions[n].getX();
            y = positions[n].getY();
            x *= size;
            y *= size;
            x += movement_x;
            y += movement_y;
            positions[n] = tlp::Coord(x,y,0);
        }
    }
    delete nodeIter;
    for (j = 0; j < n_threads - 1; j++) {
        delete[] averagePos[j];
    }
    delete[] averagePos;
}

std::map<tlp::node, tlp::Coord>  CLayoutSpace::getPositions() const {
    return positions;
}

std::map<tlp::node, int> CLayoutSpace::getTypes() const {
    return node_type;
}

bool CLayoutSpace::isBorderNode(tlp::node n, tlp::Graph* &subGraph) {
    tlp::Iterator<tlp::edge>* edgeIter = theGraph->getInOutEdges(n);
    bool borderFound = false;
    while (edgeIter->hasNext() && !borderFound) {
        tlp::edge e = edgeIter->next();
        borderFound = !subGraph->isElement(subGraph->target(e));
    }
    delete edgeIter;
    return borderFound;
}

std::vector<tlp::node> CLayoutSpace::divideNodesByType(tlp::Graph* &subGraph, int group) {
    std::vector<tlp::node> innerNodes;
    tlp::Iterator<tlp::node>* nodeIter = subGraph->getNodes();
    while (nodeIter->hasNext()) {
        tlp::node _n = nodeIter->next();
	groupAssignation[_n.id] = group;
        if (isBorderNode(_n, subGraph)) {
            node_type[_n] = BORDER_NODE;
            borderNodes.push_back(_n);
        } else {
            innerNodes.push_back(_n);
            node_type[_n] = INNER_NODE;
        }
    }
    delete nodeIter;
    if (innerNodes.size() > max_innerNodes) {
        max_innerNodes = innerNodes.size();
    }
    return innerNodes;
}



