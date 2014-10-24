/*
    Imports a Dimacs format file into Tulip
    Copyright (C) 2012  Juan David Cruz-Gomez juan.cruzgomez@telecom-bretagne.eu
    This program has been written durin my PhD thesis at Telecom-Bretagne

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
