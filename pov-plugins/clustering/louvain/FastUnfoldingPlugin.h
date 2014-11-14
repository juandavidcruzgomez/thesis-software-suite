/**
 The MIT License (MIT)

 Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne 
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


#ifndef FASTUNFOLDINGPLUGIN_H
#define FASTUNFOLDINGPLUGIN_H

#include <tulip/TulipPlugin.h>
#include <CommunitySpace.h>

/** \addtogroup clustering*/
/*@{*/

class FastUnfoldingPlugin : public tlp::Algorithm
{
public:
  /**
   * Constructor
   */
  FastUnfoldingPlugin(tlp::AlgorithmContext context);
  /**
   * Destructor
   */
  ~FastUnfoldingPlugin();
  /**
   * Executes the algorithm
   */
  bool run();
  /**
   * Check if all the data is available to execute the algorithm
   */
  bool check(std::string& error);
  /**
   * Reset the algorithm
   */
  void reset();
  
private:
  void assignEdgesToGroups();
private:
  CommunitySpace* space;
  
};

/*@}*/

#endif // FASTUNFOLDINGPLUGIN_H
