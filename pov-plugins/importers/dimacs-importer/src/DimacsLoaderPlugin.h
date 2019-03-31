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
#ifndef DIMACS_LOADER_PLUGIN_H
#define DIMACS_LOADER_PLUGIN_H

#include <tulip/TulipPlugin.h>
#include <string>

#include "CDimacsLoader.h"

namespace {
	const char * paramHelp[] = {
		//filename
		HTML_HELP_OPEN()        \
		HTML_HELP_DEF( "String", "pathname" ) \
		HTML_HELP_BODY() \
		"This parameter defines the file pathname to import." \
		HTML_HELP_CLOSE(),
	};
}


/** Import module documentation */
// MyImportModule is just an example
/*@{*/

class DimacsLoaderPlugin : public tlp::ImportModule{
public:
	DimacsLoaderPlugin(tlp::AlgorithmContext context);
	~DimacsLoaderPlugin();
	
	bool import(const std::string &name);
	
private:
	CDimacsLoader* loader;
};
/*@}*/

IMPORTPLUGINOFGROUP(DimacsLoaderPlugin, "DIMACS Import Module", "Juan David Cruz Gomez", "22/05/2012", "No comments", "1.0", "PoV Import Algorithms");
#endif
