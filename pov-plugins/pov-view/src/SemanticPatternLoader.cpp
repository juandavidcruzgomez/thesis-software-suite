/*
 * File:   SemanticPatternLoader.cpp
 * Author: juancrug
 *
 * Created on 6 février 2012, 11:46
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
