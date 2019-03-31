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
