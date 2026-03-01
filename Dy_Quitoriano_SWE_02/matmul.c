#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <sys/time.h>

#define n 3


// taken from Introduction to HPC for Scientists and Engineers
void get_walltime_(double* wcTime) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}
void get_walltime(double* wcTime) {
    get_walltime_(wcTime);  
}


// C = A * B implementation:
// its like: i x k mult k x j = i x j
void mmm(float **A, float **B, float **C, int n){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = 0.0f;
            for(int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
            
    }

}
