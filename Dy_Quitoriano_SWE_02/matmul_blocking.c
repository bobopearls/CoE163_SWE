#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <sys/time.h>

// taken from Introduction to HPC for Scientists and Engineers
void get_walltime_(double* wcTime) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}


void fill_random(float *M, int n) { //  generate random matrix values
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i*n + j] = (float)rand() / RAND_MAX;
}

void zero_matrix(float *M, int n) { // instantiate an empty matrix for C
    for (int i = 0; i < n*n; i++)
        M[i] = 0.0f;
}

/* make a matrix storage first that is continguous memory row major order:
[ a00 a01 a02
  a10 a11 a12
  a20 a21 a22 ]
  Stored as a 1D array a_ij
  [a00 a01 a02 a10 a11 a12 a20 a21 a22]
  [A[0] A[1] A[2] A[3] A[4] A[5] A[6] A[7] A[8]]
  if I want to access a12 for n=3 (3x3 matrix), i would need A[(3*1) + 2] = A[5]
  to access elements in row major order: A[(i*n) + j]
*/

// C = A * B implementation:
// its like: i x k mult k x j = i x j
void block_ijk(float *A, float *B, float *C, int n, int N){
    int blocks = n/N;
    
    //blocks
    for (int ii = 0; ii < n; ii+=blocks){
        for(int jj = 0; jj < n; jj+=blocks){
            for(int kk = 0; kk < n; kk+=blocks){
                //normal mmm code
                for(int i = ii; i < ii + blocks; i++){
                    for (int j = jj; j < jj + blocks; j++){
                        for(int k = kk; k < kk + blocks; k++){
                            C[(i*n) + j] += A[(i*n) + k] * B[(k*n) + j];
                        }
                    } 
                }
               
            }
        } 
    }
}

void block_jik(float *A, float *B, float *C, int n, int N) {
    int blocks = n/N;
    
    for(int jj = 0; jj < n; jj+=blocks){
        for (int ii = 0; ii < n; ii+=blocks){
            for(int kk = 0; kk < n; kk+=blocks){
                //normal mmm code
                 for (int j = jj; j < jj + blocks; j++){
                    for(int i = ii; i < ii + blocks; i++){
                        for(int k = kk; k < kk + blocks; k++){
                            C[(i*n) + j] += A[(i*n) + k] * B[(k*n) + j];
                        }
                    } 
                }
               
            }
        } 
    }
}

void block_ikj(float *A, float *B, float *C, int n, int N) {
    int blocks = n/N;
    
    //blocks
    for (int ii = 0; ii < n; ii+=blocks){
        for(int kk = 0; kk < n; kk+=blocks){
            for(int jj = 0; jj < n; jj+=blocks){

                //normal mmm code
                for(int i = ii; i < ii + blocks; i++){
                    for(int k = kk; k < kk + blocks; k++){
                        for (int j = jj; j < jj + blocks; j++){
                        
                            C[(i*n) + j] += A[(i*n) + k] * B[(k*n) + j];
                        }
                    } 
                }
               
            }
        } 
    }
}

void block_kij(float *A, float *B, float *C, int n, int N) {
    int blocks = n/N;
    
    //blocks
    for(int kk = 0; kk < n; kk+=blocks){
        for (int ii = 0; ii < n; ii+=blocks){
        
            for(int jj = 0; jj < n; jj+=blocks){

                //normal mmm code
                for(int k = kk; k < kk + blocks; k++){
                    for(int i = ii; i < ii + blocks; i++){
                    
                        for (int j = jj; j < jj + blocks; j++){
                        
                            C[(i*n) + j] += A[(i*n) + k] * B[(k*n) + j];
                        }
                    } 
                }
               
            }
        } 
    }
}

void block_jki(float *A, float *B, float *C, int n, int N) {
    int blocks = n/N;
    
    for(int jj = 0; jj < n; jj+=blocks){
        for(int kk = 0; kk < n; kk+=blocks){
            for (int ii = 0; ii < n; ii+=blocks){
            
                //normal mmm code
                for(int i = ii; i < ii + blocks; i++){
                    for (int j = jj; j < jj + blocks; j++){
                    
                        for(int k = kk; k < kk + blocks; k++){
                            C[(i*n) + j] += A[(i*n) + k] * B[(k*n) + j];
                        }
                    } 
                }
               
            }
        } 
    }
}

void block_kji(float *A, float *B, float *C, int n, int N) {
    int blocks = n/N;
    
    //blocks
    for(int kk = 0; kk < n; kk+=blocks){
        for(int jj = 0; jj < n; jj+=blocks){
            for (int ii = 0; ii < n; ii+=blocks){
        
            

                //normal mmm code
                for(int k = kk; k < kk + blocks; k++){
                    for (int j = jj; j < jj + blocks; j++){
                        for(int i = ii; i < ii + blocks; i++){
                    
                        
                        
                            C[(i*n) + j] += A[(i*n) + k] * B[(k*n) + j];
                        }
                    } 
                }
               
            }
        } 
    }
}

double benchmark(void (*mmm_func)(float*,float*,float*,int,int),
                 float *A, float *B, float *C,
                 int n, int N, int trials)
{
    double t_start, t_end;
    double total = 0.0;

    for (int t = 0; t < trials; t++) {

        zero_matrix(C, n);

        get_walltime_(&t_start);
        mmm_func(A, B, C, n, N);
        get_walltime_(&t_end);

        total += (t_end - t_start);
    }

    return total / trials;
}

int main(){
    printf("=== RUNNING ===\n");
    int n;
    int N;
    int trials = 30; // can change to 30

    printf("Enter matrix size n: ");
    fflush(stdout);
    
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter matrix size N: ");
    fflush(stdout);
    
    if (scanf("%d", &N) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    // Contiguous memory for A, B, C
    float *A = malloc(n * n * sizeof(float));
    float *B = malloc(n * n * sizeof(float));
    float *C = malloc(n * n * sizeof(float));

    // fill w random values
    fill_random(A, n);
    fill_random(B, n);
/*
    double t_start, t_end;
    double total_time = 0.0;


    for (int t = 0; t < trials; t++){
        zero_matrix(C, n);
        get_walltime_(&t_start);
        mmm_ijk(A, B, C, n);
        get_walltime_(&t_end);
        total_time += (t_end - t_start);
    }
 

    printf("Average time over %d trials, takes %f seconds\n",
    trials, total_time / trials);
*/ 
    // replace with one that runs all the different memory accesses
    printf("\nnumber of trials: %d\n", trials);
    printf("\nResults for n = %d\n\n", n);

    printf("ijk: %f seconds\n",
        benchmark(block_ijk, A, B, C, n, N, trials));

    printf("ikj: %f seconds\n",
        benchmark(block_ikj, A, B, C, n, N, trials));

    printf("jik: %f seconds\n",
        benchmark(block_jik, A, B, C, n, N, trials));

    printf("jki: %f seconds\n",
        benchmark(block_jki, A, B, C, n, N, trials));

    printf("kij: %f seconds\n",
        benchmark(block_kij, A, B, C, n, N, trials));

    printf("kji: %f seconds\n",
        benchmark(block_kji, A, B, C, n, N, trials));

    free(A);
    free(B);
    free(C);
    return 0;
    }
