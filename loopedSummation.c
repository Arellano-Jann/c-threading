#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <time.h>
#include <ctype.h>

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

int readFile(char filename[] , int array[]){
    return 1;
}


int main(int argc, char* argv[]){
    int* arr;
    int success = readFile(argv[0], arr);
    
    if (success == -1) return 1; // return 1 for failure

    clock_t initial_time = clock();

    // summing code
    int sum = 0;
    foreach(int *v, arr) {
        sum += *v;
    }

    clock_t final_time = clock();

    float total_time = (float) (final_time - initial_time) / CLOCKS_PER_SEC;
    printf("Total value of array: %d", sum);
    printf("Time Taken (ms): %f", total_time);
    return 1;

}