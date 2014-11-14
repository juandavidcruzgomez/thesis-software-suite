/**
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
*/
#include <iostream>
#include "matrix.h"

int main( int argc, char** argv )
{
  int rowsa = 2;
  int colsa = 3;
  float* data_a = new float[rowsa*colsa];
  float* data_b = new float[rowsa*colsa];
  for( int i = 0; i < rowsa*colsa; ++i )
  {
    data_a[i] = i%2 == 0 ? 1 : 2;
    data_b[i] = i%2 == 0 ? 1 : 2;
  }
  Matrix* left = new Matrix( rowsa, colsa, COLUMN_MAJOR, data_a );
  Matrix* right = new Matrix( colsa, rowsa, COLUMN_MAJOR, data_b );
  Matrix* result = new Matrix( colsa, colsa, COLUMN_MAJOR );
  std::cout<< "Matrix A:" << std::endl;
  left->printMatrix();
  std::cout<< "Matrix B:" << std::endl;
  right->printMatrix();
  std::cout<< "Matrix C (initial state):" << std::endl;
  result->printMatrix();
  std::cout << "----" << endl;
  right->matMult( left, result, 1 );
  std::cout<< "Matrix C = BxA:" << std::endl;
  result->printMatrix();
  
  delete left;
  delete right;
  delete result;
  return EXIT_SUCCESS;
}
