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
void* summation(void* thread_struct){
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
    int arrCount = readFile(argv[2], arr);
    
    if (arrCount == -1) return 1; // return 1 for failure

    int numThreads = atoi(argv[1]);
    int useLock = atoi(argv[3]);

    if (numThreads == 0 || (useLock != 0 && useLock != 1)) {
        printf("Please enter a number of threads that you'd like to calculate with number of threads, filename to open, and lock use value (./threadedSummation 9 tenValues.txt 1)\n")
        return 1;
    }

    numThreads = (numThreads > arrCount) ? arrCount : numThreads; // if numThreads > arrCount, set numThreads to arrCount (number of elements in array
    struct thread_data threadArray[numThreads]; // array of thread_data structs
    // thread_data* threadArray = (thread_data*) malloc(numThreads * sizeof(thread_data)); // array of thread_data structs
    pthread_t *threads = (pthread_t*) malloc(numThreads * sizeof(pthread_t)); // construct array of threads

    clock_t initial_time = clock();

    // summing code (11)
    if (useLock) pthread_mutex_init(&lock, NULL); // initialize lock
    for (int i = 0; i < numThreads; i++) {
        threadArray[i].tid = i; // thread id
        threadArray[i].useLock = useLock;
        threadArray[i].data = arr; // data array
        threadArray[i].startInd = i * (arrCount / numThreads);
        threadArray[i].endInd = (i + 1) * (arrCount / numThreads) - 1;
        if (i == numThreads - 1) threadArray[i].endInd = arrCount - 1; // fill in the left overs
        pthread_create(&threads[i], NULL, summation, (void*) &threadArray[i]);
        pthread_join(threads[i], NULL);
    }

    clock_t final_time = clock();
    if (useLock) pthread_mutex_unlock(&lock); // unlock lock at end


    // // summing code
    // foreach(int *v, arr) {
    //     sum += *v;
    // }


    float total_time = (float) (final_time - initial_time) / CLOCKS_PER_SEC * 1000;
    printf("Total value of array: %lld\n", sum);
    printf("Time Taken (ms): %f\n", total_time);
    if (uselock) pthread_mutex_destroy(&lock); // destroy lock
    pthread_exit(NULL); // exit thread
    return 1;

}


// int main(int argc, char* argv[]) {
//     clock_t start_time, end_time;
//     double total_time;

//     pthread_t* threads;
//     thread_data_t* thread_data;

//     int i, num_threads, len, use_lock;
//     int* data;

//     if (argc != 5) {
//         printf("Please enter the program name, number of threads, filename to open, and whether to lock (./threadedSummation 9 example.txt 0)\n");
//         return 1;
//     }

//     num_threads = atoi(argv[1]);
//     data = read_data(argv[2], &len);
//     use_lock = atoi(argv[3]);

//     if (num_threads > len) {
//         printf("Too many threads requested. Please enter a number of threads less than or equal to the number of data elements.\n");
//         return 1;
//     }

//     threads = (pthread_t*) malloc(num_threads * sizeof(pthread_t));
//     thread_data = (thread_data_t*) malloc(num_threads * sizeof(thread_data_t));

//     if (threads == NULL || thread_data == NULL) {
//         printf("Could not allocate memory for threads or thread data.\n");
//         return 1;
//     }

//     if (use_lock) {
//         pthread_mutex_init(&lock, NULL);
//     }

//     start_time = clock();

//     for (i = 0; i < num_threads; i++) {
//         thread_data[i].tid = i;
//         thread_data[i].useLock = use_lock;
//         thread_data[i].data = data;

//         thread_data[i].start_index = i * (len / num_threads);
//         thread_data[i].end_index = (i + 1) * (len / num_threads) - 1;

//         if (i == num_threads - 1) {
//             thread_data[i].end_index = len - 1;
//         }

//         pthread_create(&threads[i], NULL, (void*) sum_slice, (void*) &thread_data[i]);
//     }

//     for (i = 0; i < num_threads; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     end_time = clock();
//     total_time = (double