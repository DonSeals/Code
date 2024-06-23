#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>

#define NUM_THREADS 10

void *doWork(void *arg);
void enter(pthread_mutex_t *mutex_name, pthread_cond_t *condvar, int *CriticalThreads,int m);
void leave(pthread_mutex_t *mutex_name, pthread_cond_t *condvar, int *CriticalThreads);
void doCriticalWork();

typedef struct {
    pthread_mutex_t *my_mutex;
    pthread_cond_t *condvar;
    int *CriticalThreads;
    int max_threads;
} my_struct;

int main(){
    int m = 3;
    int thread_count = 0;
    pthread_cond_t var;
    pthread_mutex_t mutex;

    my_struct cond_struct = {&mutex, &var, &thread_count,m};

    if(pthread_cond_init(&var,NULL) !=0){
        printf("Failed to intitialize condition variable");//  should use perror instead
    }
    if(pthread_mutex_init(&mutex,NULL) !=0 ){
        printf("Error initializing mutex");//  should use perror instead
    }

    pthread_t thread[NUM_THREADS];
    for(int i=0; i< NUM_THREADS; i++){
        if(pthread_create(&thread[i],NULL,doWork, &cond_struct) !=0){
            printf("Error : failed to create thread.\n");//  should use perror instead
            return 1;
        }
    }
    //unnecessary if thread start_routine(function) returns itself?
    for(int i = 0; i<NUM_THREADS;i++){
        if(pthread_join(thread[i],NULL) != 0){
            printf("Error : failed to join threads\n");//  should use perror instead
            return 1;
        }

    }

if(pthread_mutex_destroy(&mutex) !=0){
    printf("Error destroying mutex");//  should use perror instead
}
if(pthread_cond_destroy(&var) != 0){
    printf("Error destroying condition variable");//  should use perror instead
}
    return 0;
}

void *doWork(void *arg){
    my_struct *args = (my_struct *)arg;
    while(true){
        enter(args->my_mutex, args->condvar, args->CriticalThreads, args->max_threads);

        doCriticalWork(args->CriticalThreads); 
            
        leave(args->my_mutex, args->condvar, args->CriticalThreads);
        // do more work (remainder section)
        sleep(1);
    }
    return NULL;
}

void enter(pthread_mutex_t *mutex,  pthread_cond_t *var, int *thread_count, int m){  // Robbins &  Robbins pg. 466 ex 13.13
    pthread_mutex_lock(mutex);
    while(*thread_count>=m){
        pthread_cond_wait(var,mutex);
    }
    (*thread_count)++;
    pthread_mutex_unlock(mutex);
    sleep(1);
}

void leave(pthread_mutex_t *mutex,  pthread_cond_t *var, int *thread_count){ // Robbins & Robbins pg 467 ex 13.14
    pthread_mutex_lock(mutex);
    (*thread_count)--;
    pthread_cond_signal(var);
    pthread_mutex_unlock(mutex);
    sleep(1);
}


void doCriticalWork(int *thread_count){
    pthread_t tid = pthread_self(); // pthread_self() returns thread ID of type pthread_t, so a variable must be initialized with this type
    printf("Thread ID: %lu is in the Critical Section - %d threads are currently running\n",tid, (*thread_count));
    sleep(1);
}