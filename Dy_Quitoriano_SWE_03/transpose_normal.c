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

// Marie change: use [i*n + j], this is what I did last time too
void transpose(float *A, float *B ,int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //A[j][i] = B[i][j];
            A[j*n + i] = B[i*n + j];
        }
    }
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

// Function for effective memory bandwidth:
double calc_bandwidth(int n, double time_sec){
    // read nxn floats and wr nxn floats
    double bytes = 2.0 * n * n * sizeof(float);
    return (bytes / time_sec) /1e9; // this is to get the result in Gigabyte/seconds
}

double benchmark(float *A, float *B, int n, int trials){
    double t_start, t_end;
    double total = 0.0;

    for (int t = 0; t < trials; t++) {

        zero_matrix(A, n);

        get_walltime_(&t_start);
        transpose(A, B, n);
        get_walltime_(&t_end);

        total += (t_end - t_start);
    }

    return total / trials;
}

// printing the transposed matrix (at least a part of it)
void print_mat(float *M, int n){
    int limit = (n > 5) ? 5 : n; // is n > 5? if yes bring 5x5, else print n 
    printf("=== MAT. SAMPLE ===\n");
    for(int i = 0; i < limit; i++){
        for(int j = 0; j < limit; j++){
            printf("%6.2f ", M[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    printf("=== RUNNING ===\n");
    int n;
    int trials = 30; // can change to 30

    printf("Enter matrix size n: ");
  
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    float *A = malloc(n * n * sizeof(float));
    float *B = malloc(n * n * sizeof(float));

    //zero_matrix(A, n);
    fill_random(B, n);

    double avg_time = benchmark(A, B, n, trials);
    double bandwidth = calc_bandwidth(n, avg_time);

    printf("\nResults for n = %d\n\n", n);
    printf("Average Time: %f seconds\n", avg_time);
    printf("Memory Bandwidth (Calculated): %f GB/s\n", bandwidth);

    // display the original and transposed matrices:
    printf("B, original:");
    print_mat(B,n);

    printf("A, transposed:");
    transpose(A, B, n);
    print_mat(A, n);

    free(A);
    free(B);
    return 0;

}
