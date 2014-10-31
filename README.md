# Juan David Cruz-Gómez PhD Thesis software suite

This repository contains several software projects developped during my PhD thesis
at Telecom - Bretagne. Since the software and algorithms were mostly written for
papers and thus in a rush, the code may not be the best and cleanest code you
may ever seen.

However, in an effort to write clean code, I try to document all the code and to
automate the building process. To do this I use CMake (I hope you know the basics
of CMake).

## Table of contents

* Installing CMake
* Installing and configuring Tulip
* Installing and configuring ATLAS
* Projects
  * 


cmake -DTULIP_DIR=/home/juancrug/tulip3 \
  -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip \
  -DATLAS_PREFIX=/home/juancrug \
  -DPREFIX=/home/juancrug \
  ..

