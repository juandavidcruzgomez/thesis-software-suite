# Point of View projects
This repository contains several [[Tulip]](http://tulip.labri.fr) plugins that belong to the PhD 
thesis of Juan David Cruz-Gomez. Most of the plugins were developped between 2010 and 2012, 
while others like the PoVLayoutPlugin has ben updated since.

## Why Point of View?
The Point of View is anotion we try to develop to indicate that the set of features describing a 
person can be divided into several different subsets that can be compared with other individuals. 
The basic idea is that, besides the potential high dimensional problems that may arise, using the 
whole set of attributes for comparing users may result bad results, mainly because of the 
singularity of each actor.

## License
Copyright (C) 2014  Juan David Cruz-Gomez and Telecom-Bretagne
juan.cruzgomez@telecom-bretagne.eu

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

#How to use this software
##Prerequisites


##Building the plugins
cmake -DTULIP_DIR=/home/juancrug/tulip3 \
  -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip \
  -DATLAS_PREFIX=/home/juancrug \
  -DMATRIX_PREFIX=/home/juancrug \
  -DMDS_PREFIX=/home/juancrug \
  -DBASE_PREFIX=/home/juancrug \
  ..

