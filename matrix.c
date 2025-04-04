#include <stdio.h>
#include <stdlib.h>

#define N 256


int i,j;
int readmatrix(size_t rows, size_t cols, int (*a)[cols], const char* filename)
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



int main(){
    int matrixA[N][N];
    readmatrix(N,N,matrixA,"matrixA.txt");    
    int matrixB[N][N];
    readmatrix(N,N,matrixB,"matrixB.txt");
    int matrixC[N][N];
    matmul(matrixA,matrixB,matrixC);
    save_to_file(matrixC,N,N,"matrixC_C.txt");

    return 0;
}