#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <assert.h>
#include <immintrin.h>
#include <xmmintrin.h>

struct timespec res;
long nano1,nano2;
#define N 256

float  A[N][N] __attribute__ ((aligned(32)));
float  B[N][N] __attribute__ ((aligned(32)));
float  C[N][N] __attribute__ ((aligned(32)));
__m256 *Am=(__m256*)A;
__m256 *Bm=(__m256*)B;
__m256 *Cm=(__m256*)C;


double get_time() {
    return (double)clock() / CLOCKS_PER_SEC;
}


int i,j;
int readmatrix(size_t rows, size_t cols, int (*a), const char* filename)
{

    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL)
        return 0;

    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < cols; ++j)
            fscanf(pf, "%d", a[i] + j);
    }
}

int readmatrix_int(size_t rows, size_t cols, __m256 (*a), const char* filename)
{

    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL)
        return 0;

    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < cols; ++j)
            fscanf(pf, "%d", a[i] + j);
    }


    fclose (pf); 
    return 1; 
}


#define block 8
void matmul(int (*a)[N],int (*b)[N],int (*c)[N]){
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int acc = 0;
            for(int k = 0; k < N; k++) {
                acc += a[i][k] * b[k][j];
            }
            c[i][j] = acc;
        }
    }
}
void matmul_int(__m256 (*Am),__m256 (*Bm), __m256 (*Cm)){
    for(int by=0;by<N;by+=block){
        for (int bx = 0; bx < N; bx+=block)
        {
            __m256 tc[block];
            for(int i=0;i<N;i++){
                __m256 tmp={};
                for(int j=0;j<N;j+=8){
                    tmp=_mm256_fmadd_ps (Am[((by+i)*N+j)/8],  Bm[(bx*N+j)/8], tmp);
            }
            tc[i]=tmp;
        }
        for(int i=0;i<N;i++){
            Cm[((by+i)*N+bx)/8]=tc[i];
        }
    }
}
}

int save_to_file(int (*a)[N], unsigned n, unsigned m, const char* filename) {
    FILE *pf = fopen(filename, "w");  // Fixed: Use write mode ("w")
    if (!pf) return 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fprintf(pf, "%d", a[i][j]);  // Write as integer
            if(j != m-1) fprintf(pf, " ");  // Add space between numbers
        }
        fprintf(pf, "\n");  // Newline after each row
    }

    fclose(pf);  // Close the file after writing
    return 1;
}
int save_to_file_int(__m256 (*a)[N], unsigned n, unsigned m, const char* filename) {
    FILE *pf = fopen(filename, "w");  // Fixed: Use write mode ("w")
    if (!pf) return 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fprintf(pf, "%d", a[i][j]);  // Write as integer
            if(j != m-1) fprintf(pf, " ");  // Add space between numbers
        }
        fprintf(pf, "\n");  // Newline after each row
    }

    fclose(pf);  // Close the file after writing
    return 1;
}



int main(){
    float  matrixA[N][N] __attribute__ ((aligned(32)));
    float  matrixB[N][N] __attribute__ ((aligned(32)));
    float  matrixC[N][N] __attribute__ ((aligned(32)));
    __m256 *Am=(__m256*)matrixA;
    __m256 *Bm=(__m256*)matrixB;
    __m256 *Cm=(__m256*)matrixC;
    readmatrix_int(N,N,matrixA,"matrixA.txt");    
    readmatrix_int(N,N,matrixB,"matrixB.txt");
    double start_time = get_time();
    matmul_int(matrixA, matrixB, matrixC);
    double end_time = get_time();

    double time_taken = end_time - start_time; // Time in seconds
    double flops = (2.0 * N * N * N) / time_taken;
    printf("Time: %.6f seconds\n", time_taken);
    printf("FLOPS: %.2f\n", flops);
    printf("GFLOPS: %.2f\n", flops / 1000000000.0);    
    save_to_file_int(matrixC,N,N,"matrixC_C.txt");

    return 0;
}