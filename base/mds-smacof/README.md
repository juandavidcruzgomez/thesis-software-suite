# README #

This is a really basic library to do MultiDimensional Scaling with SMACOF.
This is very simple (and maybe buggy, IDK) but can be useful, and indeed
I use it for other projects I'm working on.
Since I've wrote this for my own projects, other functions may be added in the future, sorry for the inconvenience.

### What do yo need? ###

* CMake
* A reasonable good C++ compiler (I use gcc 4.7.2)
* This project uses the Matrix library you can find [here](https://bitbucket.org/juandavidcruz/matrix-basic-library/).

### How do I get set up? ###

* Create a build folder at the same level of src
* Execute: 
~~~~
  cmake -DPREFIX=<prefix> \
  -DMATRIX_PREFIX=<matrix prefix> \
  ..
  make && make install
~~~~
* Done! You should find within {prefix}/lib the library binary and within  {prefix}/include the header
### What next? ###

* I don't know, it depends on the needs...
