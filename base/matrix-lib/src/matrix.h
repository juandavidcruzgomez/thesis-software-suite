/*
 This class implements a matrix container with some basic operations
 such as sum and multiplication. The multiplication has been
 implemented using ATLAS.
 This software has been developed during my PhD thesis at Telecom - Bretagne
 
 Copyright (C) 2012  Juan David Cruz Gomez juandavidcruz_at_gmail.com
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <cassert>
#include <iostream>

extern "C"{
#include "cblas.h"
}

#define ROW_MAJOR 0
#define COLUMN_MAJOR 1

#define INVALID -1.0E200

/**
 * The options:
 * NoLib: direct operations over the matrices, with no libraries
 * CBlas: using only cblas, in most cases, the Atlas version
 * CUBlas: using the blas for the GPU
 */
typedef enum {NoLib,CBlas,CUBlas} LIBTYPE;

using namespace std;

class Matrix {
public:
  /**
   * Default constructor
   */
  Matrix();
  /**
   * Constructor
   * @param _rows the number of rows
   * @param _columns the number of columns
   * @param _type the storage type
   */
  Matrix( int _rows, int _columns, int _type );
  /**
   * Constructor
   * @param _rows the number of rows
   * @param _columns the number of coumns
   * @param _type the type of storage
   * @param _data a pointer to float with the data
   */
  Matrix( int _rows, int _columns, int _type, float* _data );
  /**
   * Copy constructor
   * @param orig
   */
  Matrix(const Matrix& orig);
  /**
   * Destructor
   */
  virtual ~Matrix();
  /**
   * Assigns datum to the element [_row,_col]
   * @param _row
   * @param _column
   * @param datum
   */
  void setElement( int _row, int _col, float datum );
  /**
   * Returns the element [_row,_col] of the matrix
   * @param _row
   * @param _col
   * @return
   */
  float getElement( int _row, int _col ) const;
  /**
   *
   * @return the number of columns (m_ncol_max_ret)
   */
  int getNcols() const;
  /**
   *
   * @return the number of rows (m_nrow_max_ret)
   */
  int getNrows() const;
  /**
   * @return the maximum number of available columns in the matrix space.
   */
  int getMaxCols() const;
  /**
   * @return the maximum number of available rows in the matrix space.
   */
  int getMaxRows() const;
  /**
   *
   * @return the type of the matrix
   */
  int getNtype() const;
  /**
   * Prints the matrix out to the console
   */
  void printMatrix();
  /**
   * Reuse the existing matrix space to reduce the number of constructions/destructions
   */
  void recycleMatrixSpace( int _new_rows, int _new_cols, float* const _new_data );
  /**
   * Reuse the existing matrix space to reduce the number of constructions/destructions
   */
  void recycleMatrixSpace( int _new_rows, int _new_cols );
  /**
   *
   * @return the pointer to the elements
   */
  float* getPdmatrix() const;
  /**
   *
   * @param _newPdmatrix
   */
  void setPdmatrix( float* _newPdmatrix );
  /**
   * Returns the size of the matrix in bytes
   */
  long getSize();
  /**
   * Sums the columns for the given row
   * @param row_idx the index of the target row
   */    
  float sum_row_by_columns( int row_idx );
  /**
   * Sums the rows for the given column
   * @param column_idx the index of the target column
   */
  float sum_columns_by_row( int column_idx );
  /**
   * Transposes this matrix
   */
  void transpose();
  /**
   * Sets all the elements of the matrix to the given value
   */
  void set_all_values( float value );
  /**
   * Sets all the elements of the matrix to be zero
   */
  void set_all_zeros();
  /**
   * Sum the columns of the matrix and returns a vector of 1xm_ncols
   * @return a vector of type Matrix
   */
  Matrix* column_sum();
  /**
   * Sum the rows of the matrix and returns a vector of 1xm_nrows
   * @return a vector of type Matrix
   */
  Matrix* row_sum();
  /**
   * Creates a new matrix by concatenating two matrices by column
   * @param left_mat a n x m matrix 
   * @param right_mat a n x r matrix
   * @return the matrix [this|right_mat] of n x (m+r)
   */
  Matrix* column_rconcatenate( Matrix* right_mat );
  /**
   * Creates a new matrix by concatenating two matrices by row
   * @param top_mat a m x n matrix 
   * @param bottom_mat a r x n matrix
   * @return the matrix [this|bottom_mat] of (m+r) x n
   */
  Matrix* row_concatenate( Matrix* bottom_mat );
  /**
   * Performs the multiplication of this matrix and the rihgt matrix. 
   * C = (alpha)AxB
   * @param right_mat the right hand matrix
   * @param dest_mat the destination matrix
   * @param alpha
   */
  void matMult( Matrix* right_mat, Matrix* dest_mat, float alpha );
  
   /**
     * Search and returns the minimum element in the matrix
     * @return the minimum element
     */
    float getMinElement();
    /**
     * Search and returns the maximum element in the matrix
     * @return the maximum element
     */
    float getMaxElement();
    /**
     * Search the minimum element and returns its position
     * @return a pair containing the coordinates of the element
     */
    pair<int,int> getMinElementPos();
    /**
     * Search the maximum element and returns its position
     * @return a pair containing the coordinates of the element
     */
    pair<int,int> getMaxElementPos();
    /**
     * Removes the column given by column_idx. The columns at the right of
     * column_idx (if there's any) will be shifted to the left and the number
     * of columns will be decreased by 1.
     * @param column_idx the index of the column to be removed
     */
    void remove_column( int column_idx );
    /**
     * Removes the row given by row_idx. The rows below of
     * row_idx (if there's any) will be shifted to upwards and the number
     * of rows will be decreased by 1.
     * @param row_idx the index of the row to be removed
     */
    void remove_row( int row_idx );
    /**
     * Removes a row and the column given by row_idx and column_idx
     * @param row_idx the index of the row to be removed
     * @param column_idx the index of the column to be removed
     */
    void remove_row_col( int row_idx, int column_idx );
    /**
     * Conuts the number of elements having the value val
     * @param val the value to count on
     * @return the number of elements with the given value
     */
    int count_elements( float val );
  
  static int counter;
  
private:
  /**
   * Wraps the multiplication operation so different multiplication implementations can be used
   */
  void mat_mult_float( const LIBTYPE libtype, int M, int N, int K, const float* A, const float* B, float* C, float alpha, float beta );
  
private:
  /**
   * This is the way the matrix is stored. It could be row major (0) <br>
   * or column major (1). Note that once the type is defined it cannot be<br>
   * changed and, two matrices should be operated iff they are of the same type.
   */
  int m_ntype;
  /**
   * The maximum number of rows in the matrix. This value is set at construction time and it should not be changed, i.e., your
   * code should be made in such way you always know the maximum size you will need. Reallocation tasks are expensive.
   */
  int m_nrows;
  /**
   * The maximum number of columns in the matrix. This value is set at construction time and it should not be changed, i.e., your
   * code should be made in such way you always know the maximum size you will need. Reallocation tasks are expensive.
   */
  int m_ncols;
  /**
   * The maximum number of rows of the actual matrix. At construction time this value is the same as m_nrows, however it can be
   * changed when reusing the matrix space.
   */
  int m_nrow_max_ret;
  /**
   * The maximum number of columns of the actual matrix. At construction time this value is the same as m_ncols, however it can be
   * changed when reusing the matrix space.
   */
  int m_ncol_max_ret;
  /**
   * A pointer to float storing the elements in the matrix.
   */
  float* m_pdmatrix;
  
};

#endif // MATRIX_H
