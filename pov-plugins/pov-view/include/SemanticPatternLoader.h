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

