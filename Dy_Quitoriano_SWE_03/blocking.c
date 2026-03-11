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

// changed from transpose to blocking
void blocking(float *A, float *B ,int n, int N) {
    int blocks = n/N;
    
    for (int ii = 0; ii < n; ii+=blocks){ //added for blocking
        for(int jj = 0; jj < n; jj+=blocks){ //added for blocking
            for (int i = ii; i < ii + blocks; i++) {
                for (int j = jj; j < jj + blocks; j++) {
                    //A[j][i] = B[i][j];
                    A[j*n + i] = B[i*n + j];
                }
            }
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

double benchmark(float *A, float *B, int n, int N, int trials){
    double t_start, t_end;
    double total = 0.0;

    for (int t = 0; t < trials; t++) {

        zero_matrix(A, n);

        get_walltime_(&t_start);
        blocking(A, B, n, N);
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
    // AUTOMATED NOW
    int sizes[] = {512, 1024, 2048, 4096};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    int block_sizes[] = {8, 64, 256};
    int num_blocks = sizeof(block_sizes) / sizeof(block_sizes[0]);

    int trials = 30;
    printf("=== RUNNING ===\n");
    for (int i = 0; i < num_sizes; i++){
        int n = sizes[i];
        float *A = malloc(n * n * sizeof(float));
        float *B = malloc(n * n * sizeof(float));
        fill_random(B, n);
        printf("\nMatrix Size n = %d\n", n);
        printf("%-10s| %-15s | %-15s\n", "N (Blocks)", "Avg Time (s)", "Bandwidth (GB/s)");
        printf("------------------------------------------------------------------\n");

        for (int j = 0; j < num_blocks; j++) { //added for blocking
            int N = block_sizes[j];

            double avg_time = benchmark(A, B, n, N, trials);
            double bandwidth = calc_bandwidth(n, avg_time);

            printf("%-10d | %-15.6f | %-15.4f\n", N, avg_time, bandwidth);
        }

        free(A);
        free(B);
    }
    return 0;
    /*
    display the original and transposed matrices: used earlier to check if transp is correct
    printf("B, original:");
    print_mat(B,n);

    printf("A, transposed:");
    transpose(A, B, n);
    print_mat(A, n);

    */
    
}
