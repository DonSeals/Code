#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>

#define NUM_THREADS 10

void *doWork(void *arg);
void enter(sem_t *sem);
void leave(sem_t *sem);
void doCriticalWork();


int CriticalThreads;//use the sem to count
sem_t sem;
int m = 3;
int main(){
    if (sem_init(&sem,0,m) == -1){ // POSIX does not define a successful return value but does specify (-1) if an error occurs
        printf("Failed to initialize semaphore");
    }

    pthread_t thread[NUM_THREADS];
    for(int i=0; i< NUM_THREADS; i++){
        if(pthread_create(&thread[i],NULL,doWork, NULL) !=0){
            printf("Error : failed to create thread.\n");
            return 1;
        }
    }
    
    //unnecessary if thread start_routine(function) returns itself?
    for(int i = 0; i<NUM_THREADS;i++){
        if(pthread_join(thread[i],NULL) != 0){
            printf("Error : failed to join threads\n");
            return 1;
        }

    }
    sem_destroy(&sem);
    return 0;
}

void *doWork(void *arg){ // R. Love (LSP p.228)
    while(true){
        enter(&sem);  
        
        doCriticalWork(); 
            
        leave(&sem);
        
        sleep(1);
    }
    return NULL;
}

void enter(sem_t *sem){
    sem_wait(sem);    
}

void leave(sem_t *sem){
    sem_post(sem);
}

void doCriticalWork(){
    sem_getvalue(&sem, &CriticalThreads);
    CriticalThreads = m - CriticalThreads;
    pthread_t tid = pthread_self(); // pthread_self() returns thread ID of type pthread_t, so a variable must be initialized with this type
    printf("Thread ID: %lu is in the Critical Section - %d threads are currently running\n",tid, CriticalThreads);
    sleep(2);
}
