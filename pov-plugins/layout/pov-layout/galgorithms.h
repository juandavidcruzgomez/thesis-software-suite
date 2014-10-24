/*
 * File:   galgorithms.h
 * Author: juancrug
 *
 * Created on 28 octobre 2011, 15:52
 */

#ifndef GALGORITHMS_H
#define	GALGORITHMS_H

#include <vector>
#include <math.h>
#include <algorithm>
#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/ForEach.h>

/**
 * Calculate the Euclidean distance between two n-dimensional points
 * @param point_a the first point
 * @param point_b the second point
 * @return the distance between the points
 */
inline double euclideanDist( std::vector<double> point_a, std::vector<double> point_b ) {
    int i;
    int size = point_a.size();
    double dist = 0;
    for ( i = 0; i < size; i++ ) {
        dist += pow(abs(point_a[i]-point_b[i]),size);
    }
    return size > 0 ? pow(dist,1.0/size) : 1;
}

/**
 *
 * @param theNodes
 * @param distanceFuncPt
 * @param dis
 */
inline void graphDissmilarityMatrix(std::vector<tlp::node> &theNodes, tlp::Graph* &theGraph, double (*distanceFuncPt)(tlp::node, tlp::node, tlp::Graph* &, std::set<int>& ), float* dis) {
    int i, j;
    int size = theNodes.size();
    set<int> cache;
    for (i = 0; i < size; i++) {
        cache.clear();
        for (j = i; j < size; j++) {
            dis[(j * size) + i] = i == j ? 0.0 : distanceFuncPt(theNodes[i], theNodes[j], theGraph, cache);
            dis[(i * size) + j] = dis[(j * size) + i];
        }
    }
    cache.clear();
}
/**
 * This function calculated the similarity matrix of the graph based on certain structural similarity function AND a set of semantic distances.
 * @param theNodes set of node to produce the matrix
 * @param distanceFuncPt a pointer to teh distance function to be used
 * @param dis a pointer to teh similarity matrix
 * @param centroids a list of centroids for the nodes. These centroids represent the semantic position of each node
 */
inline void graphDissmilarityMatrix(std::vector<tlp::node> &theNodes, tlp::Graph* &theGraph, double (*distanceFuncPt)(tlp::node, tlp::node, tlp::Graph* &), float* dis, std::map<int, vector<double> >& centroids) {
    int i, j;
    int size = theNodes.size();
    for (i = 0; i < size; i++) {
        for (j = i; j < size; j++) {
            dis[(j * size) + i] = i == j ? 0.0 : 0.5*distanceFuncPt(theNodes[i], theNodes[j], theGraph)+0.5*euclideanDist(centroids[i],centroids[j]);
            dis[(i * size) + j] = dis[(j * size) + i];
        }
    }
}

inline bool nodecomparison(tlp::node a, tlp::node b) {
    return (a.id < b.id);
}

inline double cosineDistance(tlp::node node_a, tlp::node node_b, tlp::Graph* &theGraph, std::set<int>& cache) {
    int neighbors_a = theGraph->deg(node_a);
    int neighbors_b = theGraph->deg(node_b);
    int intersection = 0;
    tlp::node littleNode = neighbors_a < neighbors_b ? node_a : node_b;
    tlp::Iterator<tlp::node> *nodeIter = theGraph->getInOutNodes(littleNode);
    while (nodeIter->hasNext()) {
        tlp::node neighbor = nodeIter->next();
        if (theGraph->existEdge(node_b, neighbor, false).isValid()) {
            intersection++;
        }
    }
    delete nodeIter;
    double den = sqrt(neighbors_a * neighbors_b);
    return den == 0 ? 1.0 : 1.0 - ((double) intersection / den);

}

inline double jaccardDistance2(tlp::node node_a, tlp::node node_b, tlp::Graph* &theGraph, std::set<int>& cache) {
    int neighbors_a = theGraph->deg(node_a);
    int neighbors_b = theGraph->deg(node_b);
    int intersection = 0;
    int unionsize = 0;
    tlp::node n;
    if ( cache.size() == 0 ) {
        tlp::Iterator<tlp::node>* nodeIter = theGraph->getInOutNodes(node_a);
        while ( nodeIter->hasNext() ) {
            tlp::node n = nodeIter->next();
            cache.insert(n.id);
        }
        delete nodeIter;
    }
    tlp::Iterator<tlp::node>* nodeIter = theGraph->getInOutNodes(node_b);
    while ( nodeIter->hasNext() ) {
        tlp::node n = nodeIter->next();
        if ( cache.count(n.id) == 1 ) {
            intersection++;
        }
    }
    delete nodeIter;
    unionsize = neighbors_a + neighbors_b - intersection;
    return unionsize == 0 ? 1.0 : 1.0 - ((double) intersection / (double) unionsize);
}


inline double jaccardDistance(tlp::node node_a, tlp::node node_b, tlp::Graph* &theGraph, std::set<int>& cache) {
    int neighbors_a = theGraph->deg(node_a);
    int neighbors_b = theGraph->deg(node_b);
    int intersection = 0;
    int unionsize = 0;
    int i;
    std::vector<tlp::node> neighsa;
    std::vector<tlp::node> neighsb;
    tlp::Iterator<tlp::node> * nodeIterA = theGraph->getInOutNodes(node_a);
    while (nodeIterA->hasNext()) {
        neighsa.push_back(nodeIterA->next());
    }
    delete nodeIterA;
    std::sort(neighsa.begin(), neighsa.end(), nodecomparison);
    tlp::Iterator<tlp::node> * nodeIterB = theGraph->getInOutNodes(node_b);
    while (nodeIterB->hasNext()) {
        neighsb.push_back(nodeIterB->next());
    }
    delete nodeIterB;
    std::sort(neighsb.begin(), neighsb.end(), nodecomparison);
    if (neighbors_a < neighbors_b) {
        for (i = 0; i < neighbors_a; i++) {
            if (std::binary_search(neighsb.begin(), neighsb.end(), neighsa[i], nodecomparison) ) {
                intersection++;
            }
        }
    } else {
        for (i = 0; i < neighbors_b; i++) {
            if (std::binary_search(neighsa.begin(), neighsa.end(), neighsb[i], nodecomparison) ) {
                intersection++;
            }
        }
    }
    unionsize = neighbors_a + neighbors_b - intersection;
    return unionsize == 0 ? 1.0 : 1.0 - ((double) intersection / (double) unionsize);
}

#endif	/* GALGORITHMS_H */

