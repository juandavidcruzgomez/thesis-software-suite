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

#include "SemanticPatternLoader.h"

SemanticPatternLoader::SemanticPatternLoader(const char* _filename) {
    infile.open(_filename, ios::in);
    pattern_size = 0;
}

int SemanticPatternLoader::getPatternSize() const{
  return pattern_size;
}

void SemanticPatternLoader::loadPatterns( bool header ) {
    int charcount = 0;
    int actual_node = 0;
    if (infile.is_open()) {
	char* splitted = NULL;
        char line[BUFFER];
        memset(line, '\0', BUFFER);
        if ( header && !infile.eof() ) {
            //Read the header...
            infile.getline(line, BUFFER);
            charcount = infile.gcount();
	    if (charcount > 0) {
                splitted = strtok(line, "\t ");
		while (splitted != NULL ){
		    header_labels.push_back(string(splitted));
		    pattern_size++;
		    splitted = strtok(NULL, "\t ");
		}
	    }
	    memset(line, '\0', charcount);
        }
        while (!infile.eof()) {
            infile.getline(line, BUFFER);
            charcount = infile.gcount();
            if (charcount > 0) {
                splitted = strtok(line, "\t ");
                while (splitted != NULL ) {
                    patterns[actual_node].push_back( atof(splitted) );
                    splitted = strtok(NULL, "\t ");
                }
            }
            memset(line, '\0', charcount);
	    actual_node++;
        }
        if( patterns.size() > 0 ){
	  pattern_size = patterns[0].size();
	}
        infile.close();
    } else {
        cout << "There is something wrong with the file..." << endl;
    }

}

vector<string> SemanticPatternLoader::getHeaderLabels() const{
  return header_labels;
}

map<int, vector<float> >  SemanticPatternLoader::getPatterns() const{
  return patterns;
}
