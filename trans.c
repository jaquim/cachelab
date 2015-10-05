/* 
 * Jaquim Cadogan - 10709649
 * Wout Kooijman - 10749586
 *
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"
#include <assert.h>
#include <sys/time.h>
#include <stdint.h>

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose32(int M, int N, int A[N][M], int B[M][N]);
void transpose64(int M, int N, int A[N][M], int B[M][N]);
void transposeAsym(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */


char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int blockSize = 8;
    int* t;
    
 
    if(M == 32 && N == 32){
        for(int i = 0; i < N; i += blockSize){
            for(int j = 0; j < N; j += blockSize){
                for(int k = i; k < i + blockSize; k++){
                    for(int l = j; l < j + blockSize; l++){
                        if(k != l) B[l][k] = A[k][l];
                    }
                    // diagonal check, if so, no switch is necessary.
                    if(i == j) {
                    	t = A[k];
                    	B[k][k] = t[k];
                    }
                }
            }
        }
    }

    if(M == 61 && N == 67){
        for(int i = 0; i < N; i += blockSize){
            for(int j = 0; j < M; j += blockSize){
                for(int k = j; k < j + blockSize && k < M; k++){
                    for(int l = i; l < i + blockSize && l < N; l++){
                        B[k][l] = A[l][k];
                    }
                }
            }
        }
    }
}
/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}
char transpose_desc_32[] = "Transpose of function for a 32x32 matrix";
void transpose32(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}
char transpose_desc_64[] = "Transpose of function for a 64x64 matrix";
void transpose64(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}
char transpose_desc_Asym[] = "Transpose of function for a asymmetric matrix";
void transposeAsym(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}
/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 
    registerTransFunction(transpose32, transpose_desc_32); 
    registerTransFunction(transpose64, transpose_desc_64); 
    registerTransFunction(transposeAsym, transpose_desc_Asym); 


}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

