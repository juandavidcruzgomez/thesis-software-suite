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
#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include <tulip/Graph.h>
#include <tulip/DoubleProperty.h>

#include <math.h>

using namespace tlp;
using namespace std;
/**
 * This class implements the PageRank algorithm presented by Bryn and Page in:
 * http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf
 */

class PageRank{
public:
  PageRank( Graph* pgraph, double damping_factor, int max_iterations, double min_delta );//double damping_factor=0.85, int max_iterations=100, double min_delta=1E-5
  ~PageRank();
  
  void calculate_pagerank();
  /**
   * gets the name of the property storing the measure
   */
  string getPropertyName() const;
  
private:
  double damping_factor;
  int max_iterations;
  double min_delta;
  string property_name;
  Graph* pgraph;
  DoubleProperty* pagerank;
};

#endif
