/**
 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne

 juan.cruzgomez@telecom-bretagne.eu 
 juandavidcruz@gmail.com

 Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
 by the European Commission - subsequent versions of the 
 EUPL (the "Licence");

 You may not use this work except in compliance with the Licence.
 You may obtain a copy of the Licence at:

    https://joinup.ec.europa.eu/software/page/eupl5
  
 Unless required by applicable law or agreed to inwriting, software 
 distributed under the Licence isdistributed on an *"AS IS"* basis,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
 See the Licence for the specific language governing permissions and limitations 
 under the Licence.
*/

/**
 * This class implements a matrix container with some basic operations
 * such as sum and multiplication. The multiplication has been
 * implemented using ATLAS.
 * This software has been developed during my PhD thesis at Telecom - Bretagne
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

void Matrix::swap( int row1, int column1, int row2, int column2 ){
	assert( row1 > -1 && row1 < m_nrows && column1 > -1 && column1 < m_ncols && 
		   row2 > -1 && row2 < m_nrows && column2 > -1 && column2 < m_ncols);
	
	float element1 = getElement(row1, column1);
	float element2 = getElement( row2, column2 );
	setElement( row1, column1, element2 );
  setElement( row2, column2, element1 );
	
}

void Matrix::shift_left( int col_start ){
  assert( col_start >= 0 && col_start < m_ncols );
  //Save the staring column:
  float* start_column = new float[m_nrows];
  if( start_column != 0 ){
    for( int i = 0; i < m_nrows; i++ ){
      start_column[i] = getElement(i, col_start);
    }
    //Shift the remaining columns
    for( int i = ( col_start*m_nrows ); i < ( m_nrows*m_ncols ) - m_nrows; i++ ){
      m_pdmatrix[i] = m_pdmatrix[i+m_nrows];
    }
    //Set the last column
    for( int i = 0; i < m_nrows; i++ ){
      setElement(i, m_ncols-1, start_column[i]);
    }
    delete[] start_column;
  } 
}

void Matrix::remove_tail_col( int from_col ){
  assert( from_col >= 0 && from_col < m_ncols );
  m_ncols = m_ncols - from_col;
  
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
