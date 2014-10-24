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

#ifndef CLAYOUTSPACE_H
#define CLAYOUTSPACE_H

#include <tulip/TulipPlugin.h>

#include <matrix.h>
#include <multidimscaling.h>

#include <vector>
#include <set>
#include <queue>

#include "ExecutionLog.h"
#include "galgorithms.h"

#define BORDER_NODE 0
#define INNER_NODE 1

class CLayoutSpace {
public:
    /**
     * Default constructor
     */
    CLayoutSpace();
    /**
     * Constructor.
     * @param _theGraph a reference of the graph.
     */
    CLayoutSpace(tlp::Graph* &_theGraph);
    /**
     * Destructor
     */
    virtual ~CLayoutSpace();
    /**
     * Starts the algorithm. This is the entry point of the algorithm, from
     * here, each group of nodes will be processed
     */
    void startAlgorithm();
private:
    /**
     * Initializes the parameters and variables for the algorithm
     */
    void initialize();
    /**
     * This method controls all the calls to the specifics methods for
     * processing each one of the set of nodes. The idea of this method is
     * to implement on a later version a threaded version of the algorithm
     */
    void processGrahp();
    /**
     * This method will process the border nodes. This is the first step of the
     * layout algorithm.
     */
    void processBorderNodeSet();
    /**
     * This method is called from processGrahp() to process each set of inner
     * nodes of each community.
     */
    void processNextInnerGroup( std::vector<tlp::node> _innerNodes );
    /**
     * This is the last method of the algorithm. Here the coordinates of the
     * nodes are set to their final positions
     */
    void calculatePositionByBorderNodes();
    /**
     * Tells whether a node n is border node or not
     * @param n the node to be tested
     * @param subGraph the group to which the node belongs
     * @return true if the node is a border node, false otherwise
     */
    bool isBorderNode(tlp::node n, tlp::Graph* &subGraph);
    /**
     *
     */
    std::vector<tlp::node> divideNodesByType(tlp::Graph* &subGraph, int group);
    /**
     * Returns the calculated positions for the nodes
     */
public:
    std::map<tlp::node, tlp::Coord> getPositions() const;
    /**
     * Returns the type of the nodes
     */
    std::map<tlp::node, int> getTypes() const;
private:
    /**
     * The reference of the graph
     */
    tlp::Graph* theGraph;
    /**
     * The number of communities in the clustered graph
     */
    int n_threads;
    /**
     * The total number of inner nodes
     */
    int totalInner;
    /**
     * The total number of border nodes
     */
    int totalBorder;
    /**
     * Proportion of nodes in each community
     */
    double* proportions;
    /**
     * The number of inner nodes in each community
     */
    float* innerNodesSize;
    /**
     * The vector of border nodes
     */
    std::vector<tlp::node> borderNodes;
    /**
     * The assignation of each node to a group
     */
    std::map<int, int> groupAssignation;
    /**
     * The maximum number of inner nodes in the graph
     */
    float max_innerNodes;
    
    /**
     * The position of each node
     */
    std::map<tlp::node, tlp::Coord> positions;
    /**
     * The type of each node (border/inner=>0/1)
     */
    std::map<tlp::node, int> node_type;
    /**
     * The log for the algorithm
     */
    ExecutionLog* logger;
    //The next three member variables are used to implement the memory management schema
    /**
     * The dissimilarity matrix for MDS
     */
    Matrix* dissmat;
    /**
     * The space where the MDS is executed
     */
    MDS_space* mdsspace;
    /**
     * This is the maximum number of nodes that can be processes at the same 
     * time: the only existent dissimilarity matrix will have this size (squared)
     */
    int m_nmax_points;
    //Now some static strings to set the events to log
    /**
     * Event for the dissimilarity matrix generation
     */
    static string DIS_MAT_GENERATION_TIME;
    /**
     * Event for registering the border nodes calculation time
     */
    static string BORDER_NODES_CALC_TIME;
    /**
     * Event for registering the calculation time of each inner nodes set.
     * Each group has to add a suffix to the end of the variable name
     */
    static string INNER_NODES_CALC_TIME_;
    /**
     * Event for registering the deltas associated with each node set.
     * Each set has to add a suffix to the end of the variable name
     */
    static string DELTA_VAR_PER_SET_;
    
    
    
    

};

#endif // CLAYOUTSPACE_H
