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

#ifndef SEMANTICPATTERNLOADER_H
#define	SEMANTICPATTERNLOADER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <map>
#include <vector>

#ifndef BUFFER
#define BUFFER 1024
#endif

using namespace std;

class SemanticPatternLoader {
public:
	/**
	 * Constructor
	 */
    SemanticPatternLoader( const char* _filename );
    /**
     * A map contining the patterns. Each pattern belongs to one node, and the index corresponds to the node id;
     */
    void loadPatterns(bool header);
    /**
	 * Returns the number of features: the number of columns in the file.
	 * @return the pattern size
	 */
    int getPatternSize() const;
    /**
	 * Returns the list of headers.
	 */
    vector<string> getHeaderLabels() const;
    /**
	 * Returns the patterns table.
	 */
    map<int, vector<float> > getPatterns() const;
    
private:
    /**
     * The file descriptor
     */
    fstream infile;
    /**
     * The number of dimensions of each pattern in the data file
     */
    int pattern_size;
    /**
	 * The labels of the features: the first line of the file should contain these.
	 */
    vector<string> header_labels;
    /**
	 * The patterns
	 */
    map<int, vector<float> > patterns;
};

#endif	/* SEMANTICPATTERNLOADER_H */

