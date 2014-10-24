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
