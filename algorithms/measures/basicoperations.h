/*
 * File:   basicoperations.h
 * Author: juandavidcruz
 *
 * Created on September 18, 2011, 5:28 PM
 * This file contains the headers of basic functions for matrix operations.
 * I am trying to do these operations in the bets way, so I will use only Column Major order <br>
 * that way I use the same structure and parameters for CBlas and CUBlas
 */

#ifndef BASICOPERATIONS_H
#define	BASICOPERATIONS_H

#define BLOCKSIZE 100

#include <stdio.h>
#include <cassert>
#include <math.h>

extern "C"{
    #include "cblas.h"
}

#include "matrix.h"

void mat_mult_float( int M, int N, int K, const float* A, const float* B, float* C, float alpha, float beta );


#endif	/* BASICOPERATIONS_H */
