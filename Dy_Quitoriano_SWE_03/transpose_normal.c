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

void transpose(float **A, float **B ,int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            A[j][i] = B[i][j];
        }
    }
}


double benchmark(void (*mmm_func)(float*,int),
                 float *A, float *B,
                 int n, int trials)
{
    double t_start, t_end;
    double total = 0.0;

    for (int t = 0; t < trials; t++) {

        zero_matrix(C, n);

        get_walltime_(&t_start);
        transpose(A, B, n);
        get_walltime_(&t_end);

        total += (t_end - t_start);
    }

    return total / trials;
}

int main(){
    printf("=== RUNNING ===\n");
    int n;
    int trials = 30; // can change to 30

    printf("Enter matrix size n: ");
    fflush(stdout);
    
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }


    float *A = malloc(n * n * sizeof(float));
    float *B = malloc(n * n * sizeof(float));

    zero_matrix(A, n);
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

    printf("Transposed: %f seconds\n",
        benchmark(transpose, A, B, n, trials));

    free(A);
    free(B);
    return 0;

}
