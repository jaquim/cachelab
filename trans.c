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

    if(N == 32){
        transpose32(M, N, A, B);
    }
    else if(N == 64){
        transpose64(M, N, A, B);
    }
    else if(N == 61 || M == 67){
        transposeAsym(M, N, A, B);
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
void transpose32(int M, int N, int A[N][M], int B[M][N], int blockRow, int blockCol, int p0, int p1)
{
    int blockRow,blockCol,k,p0,p1,p2,p3,p4,p5,p6,p7;
    int d = 0;
    int* t;

    for(blockRow = 0; blockRow < N; blockRow += 8){
            for(blockCol = 0; blockCol < M; blockCol += 8){
                for(p0 = blockRow; p0 < blockRow + 8; p0++){
                    t = A[p0];
                    if(blockRow == blockCol) d = t[p0];
                    for(p1 = blockCol; p1 < blockCol + 8; p1++){
                        if(p0 != p1) B[p1][p0] = A[p0][p1];
                    }
                    if(blockRow == blockCol)B[p0][p0] = d;
                }
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

