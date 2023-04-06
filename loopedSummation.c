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

int readFile(char filename[] , int* array){
    FILE *file = fopen(filename, "r");
    int count = 0;
    printf("Reading data...\n");

    if (file == NULL) {
        printf("File not found...\n");
        return -1;
    }

    while (fscanf(file, "%d", &array[count]) != EOF) count++;

    return count;
}


int main(int argc, char* argv[]){
    int arr[1000];
    int success = readFile(argv[1], arr);
    
    if (success == -1) return 1; // return 1 for failure

    clock_t initial_time = clock();

    // summing code
    long long int sum = 0;
    foreach(int *v, arr) {
        sum += *v;
    }

    clock_t final_time = clock();

    float total_time = (float) (final_time - initial_time) / CLOCKS_PER_SEC * 1000;
    printf("Total value of array: %lld\n", sum);
    printf("Time Taken (ms): %f\n", total_time);
    return 1;

}