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

#ifndef POVLAYOUTDISTORTION_H
#define POVLAYOUTDISTORTION_H

/**
 * This class provides methods to apply a distortion operation to a given layout to show the impact of a selected point of view.
 * The idea is: given a point of view (and the partition induced by it) calculate the centroids of the nodes inside the interaction
 * zone belonging to each community in the partition induced by the point of view. These centroids allow having influence zones,
 * calculated according to the size of the nodes involved.
 * Then, the nodes will be pushed near their centroids to see how interacting node are similar in terms of the point of view. The last
 * step is to change the colors of the inner nodes (and the border nodes maybe?) according to the partition induced by the point of view.
 * This belong to the model layer.
 */

#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/LayoutProperty.h>

#include <iostream>

class Model;

using namespace std;
using namespace tlp;

class PoVLayoutDistortion
{

public:
    /**
     * Default constructor.
     */
    PoVLayoutDistortion();
    /**
     * Constructor the receives the reference of the model
     */
    PoVLayoutDistortion( Model* _model );
    /**
     * Destructor
     */
    ~PoVLayoutDistortion();
    /**
     * Funtion called from the view to execute the distortion of the nodes according to the given point of view.
     * Returns true when finished, this way the model knows it and can inform the controller
     */
    bool performDistortion( string pov_name );

private:
    /**
     * Calculates the centroids derived by the point of view.This function uses the pov name to select the groups
     * belonging to this point of view and performe the calculations.
     */
    void calculateCentroids( vector< node > border_nodes, string pov_name );
    /**
     * Change the colors of the nodes according the selected point of view.This function uses the pov name to select the groups
      * belonging to this point of view and performe the calculations.
     */
    void changeColors(string pov_name);
    /**
     * Move the node to it's new position. This position is somewhere the straight line connecting the point to its centroid. The 
     * position is given bt ratio (0.5 = halfway)
     */
    void changePosition( node n, Coord actual_pos, std::pair< float, float > centroid, float ratio, LayoutProperty* actualLayout );

private:
    /**
     * A pointer to the model to keep the reference.
     */
    Model* model;
    /**
     * This map contains the assignation of a list of nodes to each centroid: the index is the index of the centroid, and the
     * value is the list of nodes belonging to it.
     */
    map<int,vector<node*> > centroid_assignation;
    /**
     * This map contains the coordinates of each centroid.
     */
    map<int, pair<float,float> > centroid_coords;
    
    LayoutProperty* viewLayout;
};

#endif // POVLAYOUTDISTORTION_H
