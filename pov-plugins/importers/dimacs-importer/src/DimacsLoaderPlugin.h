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
