#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <time.h>
#include <ctype.h>


int arraySum = 0;
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
    
}

int readFile(char filename[] , int array[]){
    return 1;
}


int main(int argc, char* argv[]){
    return 1;   
}