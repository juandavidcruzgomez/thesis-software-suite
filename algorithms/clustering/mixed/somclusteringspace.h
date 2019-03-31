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

/**
 * This class executes the SOM initialization and training. In general, the clsutering algoritmh.
 * Other resposibilities include:
 * - Load the patterns from the file
 * - Set the size of the map
 * - Perform the training
 * - Assign each element to a group
 */
#ifndef SOMCLUSTERINGSPACE_H
#define SOMCLUSTERINGSPACE_H

#include <tulip/Graph.h>
#include <tulip/IntegerProperty.h>
#include <tulip/DoubleProperty.h>
#include <sstream>

#include "kohonenmap.h"

using namespace tlp;
using namespace std;

class SOMClusteringSpace
{

public:
  /**
   * Constructor
   * Builds a space for SOM clustering. 
   * @param pGraph a pinter to the target graph
   * @param patterns_prop_name the name of the property containing the patterns to train the SOM map
   * @param _iterations max number of iteratiosn for the algorithm
   * @param _lambda 
   * @param _epsilon the minimum error to stop (the algorithm has converged)
   * @param _learning_rate 
   */
  SOMClusteringSpace( Graph* pGraph, string patterns_prop_name, int _iterations, int _lambda, float _epsilon, float _learning_rate );
  /**
   * Destructor
   */
  virtual ~SOMClusteringSpace();
  /**
   * Starts the algorithm. 
   * @return true if the algorithm went through and everything was okay. False otherwise
   */
  bool start_algorithm();
  /**
   * Initilizes the algorithm structures and set for them the good parameters. This include the
   * actual load of the patterns and the definition of the size of the map.
   * @return true if the initialization wes okay, false otherwise
   */
  bool initialize_algorithm();
  /**
   * Takes the final assignation and converts it to a map group_id=>list of indices
   */
  void getPartitionConfiguration();
  /**
   * Gets the assignation vector found by the algorithm
   * @return the assignation vector
   */
  vector<int> getAssignation() const;
  
private:

  /**
   * Performs the competiton to find the closest neuron to the presented pattern
   * @param _actual_pattern
   * @return the index of the winner neuron
   */
  int competition(node n);
  /**
   * Executes the competition step by changing the weights of the neuron and its max_neighs neighbors
   * @param _actual_pattern
   * @param winner_index
   * @param max_neighs
   */
  void cooperation(node n, int winner_index);
  
  inline int belongs_to( int value, vector<int>& some_array ){
    unsigned int i = 0;
    while( i < some_array.size() && some_array.at(i) != value ){
      i++;
    }
    return i<some_array.size() ? i : -1;
  }
private:
  /**
   * Where the neurons are stored
   */
  KohonenMap* theMap;
  /**
   * A pointer to the graph
   */
  Graph* pGraph;
  /**
   * The name of the property containing the patterns of the composition variable
   */  
  string patterns_prop_name;
  
  DoubleVectorProperty* patterns;
  
  int iterations;
  
  int lambda;
  
  float epsilon;
  
  float learning_rate;
  
  vector<int> assignation;
};

#endif // SOMCLUSTERINGSPACE_H
