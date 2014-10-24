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
#include "DimacsLoaderPlugin.h"


DimacsLoaderPlugin::DimacsLoaderPlugin(tlp::AlgorithmContext context) : tlp::ImportModule(context){
	addParameter<std::string>("file::name",paramHelp[0]);
	loader = NULL;
}

DimacsLoaderPlugin::~DimacsLoaderPlugin(){
	if( loader != NULL ){
		delete loader;
	}
	loader = NULL;
}

bool DimacsLoaderPlugin::import(const std::string &name){
	std::string filename;
	if (!dataSet->get("file::name", filename)){
		return false;
	}
	loader = new CDimacsLoader( graph );
	loader->loadGraph(filename);
	return true;
}
