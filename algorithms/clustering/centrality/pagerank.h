/**
 The MIT License (MIT)

 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne 
 juan.cruzgomez@telecom-bretagne.eu

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
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
