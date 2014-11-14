#include "basicoperations.h"

void mat_mult_float(int M, int N, int K, const float* A, const float* B, float* C, float alpha, float beta) {
  int lda, ldb, ldc;
  lda = M; 
  ldb = K; 
  ldc = M; 
  cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
}
