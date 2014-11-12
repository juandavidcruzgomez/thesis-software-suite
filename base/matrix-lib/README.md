# Matrix manipulation library

This is a really basic library for manipulating matrices, including multiplication, sum, column and row sum. 

Since I've wrote this for my own projects, other functions may be added in the future, sorry for the inconvenience.

One interesting feature is the memory recycling that is done when the same operation is performed over matrices of different size. I made this for coping with the memory when writing the MDS-SMACOF algorithm. In such a way the library asks for memory for the biggest matrix, and then it starts to reusing this space for the other matrices, just changing the limits (size of the matrix) as needed.

I wrote this as a part of my PhD thesis, sometimes in a rush, however I tried to write tidy code and neat documentation, if you find some trouble using this piece of software, please forgive me.

If you have any comment please, feel free to [drop me a line](juan.cruzgomez@telecom-bretagne.eu).

## License
The MIT License (MIT)

Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne
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
-------------------------------------------------------
## Compiling and installing the algorithms
###Requisites
* A reasonable good C++ compiler (I use gcc 4.7.2)
* Install CMake
* An ATLAS installation (Please refer to the [http://math-atlas.sourceforge.net/atlas_install/atlas_install.html](ATLAS installation page) for
further information regarding the configuration)

###Compiling the code
* Go to the base folder:
~~~~
juancrug@juandavid-office:~$ cd path-to-repo/software-suite/base/matrix-lib
~~~~
* Create a build folder and go into it:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/matrix-lib/$ mkdir build
juancrug@juandavid-office:~/path-to-repo/software-suite/base/matrix-lib/$ cd build
~~~~
* Configure with Cmake:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/matrix-lib/build$ cmake -DATLAS_PREFIX=/home/juancrug \
  -DPREFIX=/home/juancrug \
  ..
~~~~
**Note:** replace the configuration paths with your own, custom paths.

* Build and install:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/matrix-lib/build$ make && make install
~~~~

At this stage the libraries should be installed in /PREFIX/lib while the public interfaces (.h files) should be in /PREFIX/

## What next?

Now you should have a basic, yet nice, matrix library that hides the calls to
ATLAS (and in the future, to CUBLAS). 

Remember that this library is part of a bigger project.
