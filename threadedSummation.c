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

long long int sum = 0;
pthread_mutex_t lock;

typedef struct thread_data{
    int tid;
    int *data;
    int startInd;
    int endInd;
    int useLock; //add
} thread_data;

// don't fucking know what this int is tbh
void* summation(void* thread_struct, int i){
    thread_data* data = (thread_data*) thread_struct;

    if (data->useLock) pthread_mutex_lock(&lock); // use lock?

    // summing code
    long long int total = 0;
    for (int i = data->start; i <= data->end; i++) {
        total += data->data[i];
    }
    sum += total;

    if (data->useLock) pthread_mutex_unlock(&myMutex); // unlock lock at end

    pthread_exit(NULL); // exit thread
}


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
    printf("Reading data...\n")
    if (argc == 2) {
        printf("File not found...\n")
        return 1;
    }
    if (argc == 3) {
        printf("Please enter a number of threads that you'd like to calculate with number of threads, filename to open, and lock use value (./threadedSummation 9 tenValues.txt 1)\n")
        return 1;
    }

    int arr[1000];
    int success = readFile(argv[1], arr);
    
    if (success == -1) return 1; // return 1 for failure

    clock_t initial_time = clock();

    // summing code
    foreach(int *v, arr) {
        sum += *v;
    }

    clock_t final_time = clock();

    float total_time = (float) (final_time - initial_time) / CLOCKS_PER_SEC * 1000;
    printf("Total value of array: %lld\n", sum);
    printf("Time Taken (ms): %f\n", total_time);
    return 1;

}