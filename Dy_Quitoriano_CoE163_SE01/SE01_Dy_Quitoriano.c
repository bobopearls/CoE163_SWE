#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int find_min_combi(int num_dials, int start, int end) {
    int turns = 0;

    for (int i = 0; i < num_dials; i++) {
        int start_digit = start % 10; //get the first digit
        int end_digit = end % 10;

        int distance = start_digit - end_digit;
        if (distance < 0) { //incase negative
            distance = end_digit - start_digit; 
        }

        int val_from_ten = 10 - distance; //wrap around
        //there are two values calculated. distance is going one way while val_from_ten is going the other
        if (distance >= val_from_ten) { //if the val_from_ten way is faster
            turns += val_from_ten;
        } else { //if the distance way is faster
            turns += distance;
        } 

        start = floor(start/10);
        end = floor(end/10);
    }
    return turns;
}

int main() {
    /*
    int input;
    int start_comb;
    int end_comb;
    scanf( "%d %d %d", &input, &start_comb, &end_comb);
    printf("%d", find_min_combi(input, start_comb, end_comb));
    */
    
    clock_t start = clock() ; //https://stackoverflow.com/questions/5644730/c-measuring-computing-time
    for (int i = 0; i < 5000000; i++) {
        find_min_combi(5, 17392, 84209);
    }
    clock_t end = clock() ;
    double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC ;
    printf("%f", elapsed_time);
    
    return 0;
}

