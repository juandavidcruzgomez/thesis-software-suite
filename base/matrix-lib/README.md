# README #

This is a really basic library for manipulating matrices, including 
multiplication, sum, column and row sum. 

Since I've wrote this for my own projects, other functions may be added in the 
future, sorry for the inconvenience.

One interesting feature is the memory recycling that is done when the same 
operation is performed over matrices of different size. I made this for coping
with the memory when writing the MDS-SMACOF algorithm. In such a way the library
asks for memory for the biggest matrix, and then it starts to reusing this space
for the other matrices, just changing the limits (size of the matrix) as needed.

I wrote this as a part of my PhD thesis, sometimes in a rush, however I tried to
write tidy code and neat documentation, if you find some trouble using this
piece of software, please forgive me.

If you have any comment please, feel free to [juan.cruzgomez@telecom-bretagne.eu](drop me a line).

### Preliminaries
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

You can find a copy of the GPLv2 [http://www.gnu.org/licenses/gpl-2.0.html](here).

### What do yo need? ###

* A reasonable good C++ compiler (I use gcc 4.7.2)
* CMake
* An ATLAS installation (Please refer to the [http://math-atlas.sourceforge.net/atlas_install/atlas_install.html](ATLAS installation page) for
further information regarding the configuration)

### How do I set the thing up? ###

* Create a build folder at the same level of src
* Execute: 
~~~~
  cmake -DPREFIX=<prefix> \
    -DATLAS_PREFIX=<atlas prefix> \
    ..
  make && make install
~~~~
* Done! You should find within {prefix}/lib the library binary and within 
{prefix}/include the header

### What next? ###

Now you should have a basic, yet nice, matrix library that hides the calls to
ATLAS (and in the future, to CUBLAS). 

Remember that this library is part of a bigger project.
