/*
 This class implements a matrix container with some basic operations
 such as sum and multiplication. The multiplication has been
 implemented using ATLAS.
 This software has been developed during my PhD thesis at Telecom - Bretagne
 
 Copyright (C) 2012  Juan David Cruz Gomez juandavidcruz_at_gmail.com
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "matrix.h"

int Matrix::counter = 0;

Matrix::Matrix() {
  m_ncols = 0;
  m_nrows = 0;
  m_ncol_max_ret = 0;
  m_nrow_max_ret = 0;
  m_ntype = ROW_MAJOR;
  m_pdmatrix = NULL;
  
}

Matrix::Matrix( int _rows, int _columns, int _type ) {
  assert(_rows > 0 && _columns > 0 && (_type==ROW_MAJOR || _type==COLUMN_MAJOR) );
  m_nrows = _rows;
  m_ncols = _columns;
  m_ncol_max_ret = m_ncols;
  m_nrow_max_ret = m_nrows;
  m_ntype = _type;
  m_pdmatrix = new float[m_nrows*m_ncols];
  counter++;
}

Matrix::Matrix( int _rows, int _columns, int _type, float* _data ) {
  assert(_rows > 0 && _columns > 0 && (_type==ROW_MAJOR || _type==COLUMN_MAJOR) && _data != NULL );
  m_nrows = _rows;
  m_ncols = _columns;
  m_ncol_max_ret = m_ncols;
  m_nrow_max_ret = m_nrows;
  m_ntype = _type;
  m_pdmatrix = _data;
  counter++;
}

Matrix::Matrix(const Matrix& orig) {
  if ( this->m_pdmatrix != NULL ) {
    delete[] m_pdmatrix;
    m_pdmatrix = NULL;
  }
  m_ncol_max_ret = orig.getNcols();
  m_nrow_max_ret = orig.getNrows();
  m_ncols = orig.getMaxCols();
  m_nrows = orig.getMaxRows();
  m_ntype = orig.getNtype();
  m_pdmatrix = orig.getPdmatrix();
}

Matrix::~Matrix() {
  if ( counter > 0 ) {
    if ( this->m_pdmatrix != NULL ) {
      delete[] m_pdmatrix;
      m_pdmatrix = NULL;
      counter--;
    }
  }
}

int Matrix::getNcols() const {
  return m_ncol_max_ret;
}
int Matrix::getNrows() const {
  return m_nrow_max_ret;
}

int Matrix::getMaxCols() const {
  return m_ncols;
}
int Matrix::getMaxRows() const {
  return m_nrows;
}
int Matrix::getNtype() const {
  return m_ntype;
}
float* Matrix::getPdmatrix() const {
  return m_pdmatrix;
}

void Matrix::setPdmatrix( float* _newPdmatrix ) {
  if ( this->m_pdmatrix != NULL && _newPdmatrix != NULL ) {
    for ( int i = 0; i < m_nrow_max_ret; i++ ) {
      for ( int j = 0; j < m_ncol_max_ret; j++ ) {
        m_ntype == ROW_MAJOR ? m_pdmatrix[(i*m_ncol_max_ret) + j] = _newPdmatrix[(i*m_ncol_max_ret) + j] : m_pdmatrix[(j*m_nrow_max_ret) + i] = _newPdmatrix[(j*m_nrow_max_ret) + i];
      }
    }
  }
}

float Matrix::getElement( int _row, int _col ) const {
  assert( _row > -1 && _row < m_nrow_max_ret && _col > -1 && _col < m_ncol_max_ret );
  return m_ntype == ROW_MAJOR ? m_pdmatrix[(_row*m_ncol_max_ret) + _col] : m_pdmatrix[(_col*m_nrow_max_ret) + _row];
}

void Matrix::setElement(int _row, int _col, float datum) {
  assert( _row > -1 && _row < m_nrow_max_ret && _col > -1 && _col < m_ncol_max_ret );
  m_ntype == ROW_MAJOR ? m_pdmatrix[(_row*m_ncol_max_ret) + _col] = datum : m_pdmatrix[(_col*m_nrow_max_ret) + _row] = datum;
}

void Matrix::printMatrix() {
  int i,j;
  if ( m_ntype==ROW_MAJOR) {
    for ( i = 0; i < m_nrow_max_ret; i++ ) {
      for ( j = 0; j < m_ncol_max_ret; j++ ) {
        if ( j == m_ncol_max_ret-1 ) {
          cout << m_pdmatrix[(i*m_ncol_max_ret) + j];
        } else {
          cout << m_pdmatrix[(i*m_ncol_max_ret) + j] << "\t";
        }
      }
    }
  } else {
      for ( i = 0; i < m_nrow_max_ret; i++ ) {
        for ( j = 0; j < m_ncol_max_ret; j++ ) {
          if ( j == m_ncol_max_ret-1 ) {
            cout << m_pdmatrix[(j*m_nrow_max_ret) + i];
          } else {
            cout << m_pdmatrix[(j*m_nrow_max_ret) + i] << "\t";
          }
        }
        cout << endl;
      }
  }
  cout << endl;
}

long Matrix::getSize() {
  long size = 0;
  size = m_nrow_max_ret*m_ncol_max_ret*sizeof(*m_pdmatrix)+sizeof(this->m_ntype);
  return size;
}

float Matrix::sum_row_by_columns( int row_idx )
{
  assert( row_idx >= 0 && row_idx < m_nrow_max_ret );
  float result = 0;
  for( int i = 0; i < m_ncol_max_ret; i++ )
  {
    result += getElement( row_idx, i );
  }
  return result;
}

float Matrix::sum_columns_by_row( int column_idx )
{
  assert( column_idx >= 0 && column_idx < m_ncol_max_ret );
  float result = 0;
  for( int i = 0; i < m_nrow_max_ret; i++ )
  {
    result += getElement( i, column_idx );
  }
  return result;
}

void Matrix::transpose(){
	//I need only to change some elements of the matrix. The pointer is the same, only the positions
	//are changed
	float* _pmatrix = new float[m_nrow_max_ret*m_ncol_max_ret];
	int index = 0;
	int new_index = 0;
	for( int i = 0; i < m_nrow_max_ret; i ++ ){
		for( int j = 0; j < m_ncol_max_ret; j++ ){
			if( m_ntype == ROW_MAJOR ){
				index = ( i*m_ncol_max_ret ) + j;
				new_index = ( j*m_nrow_max_ret ) + i;
			}else{
				index = ( j*m_nrow_max_ret ) + i;
				new_index = ( i*m_ncol_max_ret ) + j;
			}
			_pmatrix[new_index] = m_pdmatrix[index];
		}
	}
	int ncols = m_ncol_max_ret;
	m_ncol_max_ret = m_nrow_max_ret;
	m_nrow_max_ret = ncols;
	delete[] m_pdmatrix;
	m_pdmatrix = _pmatrix;
}

void Matrix::set_all_values( float value )
{
  for( int i = 0; i < m_nrow_max_ret*m_ncol_max_ret; i ++ )
  {
    m_pdmatrix[i] = value;
  }
}

void Matrix::set_all_zeros()
{
  set_all_values( 0.0 );
}

void Matrix::recycleMatrixSpace( int _new_rows, int _new_cols, float* const _new_data ) {
  if ( _new_cols <= m_ncols ) {
    m_ncol_max_ret = _new_cols;
  }
  if ( _new_rows <= m_nrows ) {
    m_nrow_max_ret = _new_rows;
  }
  for ( int i = 0; i < m_nrow_max_ret; i++ ) {
    for ( int j = 0; j < m_ncol_max_ret; j++ ) {
      m_ntype == ROW_MAJOR ? m_pdmatrix[(i*m_ncol_max_ret) + j] = _new_data[(i*m_ncol_max_ret) + j] : m_pdmatrix[(j*m_nrow_max_ret) + i] = _new_data[(j*m_nrow_max_ret) + i];
    }
  }
}

void Matrix::recycleMatrixSpace( int _new_rows, int _new_cols ) {
  if ( _new_cols <= m_ncols ) {
    m_ncol_max_ret = _new_cols;
  }
  if ( _new_rows <= m_nrows ) {
    m_nrow_max_ret = _new_rows;
  }
}

Matrix* Matrix::column_sum() 
{
  Matrix* col_sum = new Matrix( 1, m_ncol_max_ret, COLUMN_MAJOR );
  for ( int i = 0; i < m_ncol_max_ret; i++ ) 
  {
    float sum = 0;
    for ( int j = 0; j < m_nrow_max_ret; j++ ) 
    {
      sum += getElement(j, i);
    }
    col_sum->setElement(0, i, sum);
  }
  return col_sum;
}

Matrix* Matrix::row_sum() 
{
  Matrix* row_sum = new Matrix( 1, m_nrow_max_ret, COLUMN_MAJOR );
  for ( int i = 0; i < m_nrow_max_ret; i++ ) 
  {
    float sum = 0;
    for ( int j = 0; j < m_ncol_max_ret; j++ ) 
    {
      sum += getElement(i, j);
    }
    row_sum->setElement(0, i, sum);
  }
  return row_sum;
}

Matrix* Matrix::column_rconcatenate( Matrix* right_mat )
{
  assert( right_mat != 0 && this->getNrows() == right_mat->getNrows() );
  int rows = this->getNrows();
  int left_cols = this->getNcols();
  int right_cols = right_mat->getNcols();
  Matrix* resulting_mat = new Matrix(rows, (left_cols+right_cols), COLUMN_MAJOR );
  for( int i = 0; i < rows; ++i )
  {
    for( int j = 0; j < left_cols; ++j )
    {
      float l_element = this->getElement(i,j);
      resulting_mat->setElement( i,j, l_element );
    }
    for( int j = 0; j < right_cols; ++j )
    {
      float r_element = right_mat->getElement(i,j);
      resulting_mat->setElement( i,left_cols+j, r_element );
    }
  }
  return resulting_mat;
}

Matrix* Matrix::row_concatenate( Matrix* bottom_mat )
{
  assert( bottom_mat != 0 && this->getNcols() == bottom_mat->getNcols() );
  int cols = this->getNcols();
  int top_rows= this->getNrows();
  int bottom_rows = bottom_mat->getNrows();
  Matrix* resulting_mat = new Matrix(( top_rows+bottom_rows), cols, COLUMN_MAJOR );
  for( int j = 0; j < cols; j++ )
  {
    for( int i = 0; i < top_rows; i++ )
    {
      resulting_mat->setElement( i, j, this->getElement(i,j));
    }
    for( int i = 0; i < bottom_rows; i++ )
    {
      resulting_mat->setElement( top_rows+i, j, bottom_mat->getElement(i,j));
    }
  }
  return resulting_mat;
}

float Matrix::getMinElement()
{
  float min = 1E26;
  for( int i = 0; i < m_nrow_max_ret*m_ncol_max_ret; ++i )
  {
    float actual_val = m_pdmatrix[i];
    if( actual_val < min )
    {
      min = actual_val;
    }
  }
  return min;
}

float Matrix::getMaxElement(){
  float max = -1E26;
  for( int i = 0; i < m_nrow_max_ret*m_ncol_max_ret; ++i )
  {
    float actual_val = m_pdmatrix[i];
    if( actual_val > max )
    {
      max = actual_val;
    }
  }
  return max;
}

pair<int,int> Matrix::getMinElementPos()
{
  float min = 1E26;
  pair<int,int> index(-1,-1);
  for( int i = 0; i < m_nrow_max_ret; ++i )
  {
    for( int j = 0; j < m_ncol_max_ret; ++j )
    {
      float actual_val = getElement(i,j);
      if( actual_val < min )
      {
	min = actual_val;
	index.first = i;
	index.second = j;
      }
    }
  }
  return index;
}

pair<int,int> Matrix::getMaxElementPos(){
  float max = -1E26;
  pair<int,int> index(-1,-1);
  for( int i = 0; i < m_nrow_max_ret; ++i )
  {
    for( int j = 0; j < m_ncol_max_ret; ++j )
    {
      float actual_val = getElement(i,j);
      if( actual_val > max )
      {
	max = actual_val;
	index.first = i;
	index.second = j;
      }
    }
  }
  return index;
}

void Matrix::remove_column( int column_idx )
{
  assert( column_idx >= 0 && column_idx < m_ncol_max_ret );
  for( int j = column_idx; j < m_ncol_max_ret; ++j )
  {
    if( j + 1 < m_ncol_max_ret  )
    {
      for( int i = 0; i < m_nrow_max_ret; ++i )
      {
	setElement(i,j, getElement(i,j+1));
      }
    }
  }
  m_ncol_max_ret--;
}

void Matrix::remove_row( int row_idx )
{
  assert( row_idx >= 0 && row_idx < m_nrow_max_ret );
  float* _p_dmatrix = new float[m_ncol_max_ret*(m_nrow_max_ret-1)];
  for( int i = 0; i < row_idx; ++ i )
  {
    for( int j = 0; j < m_ncol_max_ret; ++j )
    {
      _p_dmatrix[((m_nrow_max_ret-1)*j)+i] = getElement(i,j);
    }
  }
  for( int i = row_idx; i < m_nrow_max_ret; ++i )
  {
    if( i + 1 < m_nrow_max_ret ){
      for( int j = 0; j < m_ncol_max_ret; ++j )
      {
	_p_dmatrix[((m_nrow_max_ret-1)*j)+i] = getElement(i+1,j);
      }
      cout << endl;
    }
  }
  m_nrow_max_ret--;
  delete[] m_pdmatrix;
  m_pdmatrix = _p_dmatrix;
}

void Matrix::remove_row_col( int row_idx, int column_idx )
{
  remove_row( row_idx );
  remove_column( column_idx );
}

int Matrix::count_elements( float val )
{
  int result = 0;
  for( int i = 0; i < (m_ncol_max_ret*m_nrow_max_ret); ++i )
  {
    if( m_pdmatrix[i] == val )
    {
      result++;
    }
  }
  return result;
}

void Matrix::matMult( Matrix* right_mat, Matrix* dest_mat, float alpha )
{
  assert( right_mat != 0 && dest_mat != 0 && right_mat->getNrows() == m_ncol_max_ret && dest_mat->getNrows() == m_nrow_max_ret && dest_mat->getNcols() == right_mat->getNcols());
  int right_mat_cols = right_mat->getNcols();  
  //float* new_p_matrix = new float[m_nrow_max_ret * right_mat_cols];
  mat_mult_float(CBlas, m_nrow_max_ret, right_mat_cols, m_ncol_max_ret, this->getPdmatrix(), right_mat->getPdmatrix(), dest_mat->getPdmatrix(), alpha, 0.0f);
}

void Matrix::mat_mult_float( const LIBTYPE libtype, int M, int N, int K, const float* A, const float* B, float* C, float alpha, float beta )
{
  switch (libtype) {
    case CBlas:
    {
      int lda, ldb, ldc;
      lda = M; 
      ldb = K; 
      ldc = M; 
      cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
    }
      break;
    default:
      cerr << "Unknown library." << endl;
      break;
  }

}
