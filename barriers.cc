#include<iostream>
#include<pthread.h>
using namespace std;

class Barrier
{
    public:
    Barrier(int n); // constructor
    ~Barrier(); //destructor
    void wait();

    private:
    pthread_cond_t cond_var;
    pthread_mutex_t mtx;
    int counter;
    int num_threads;

};
void* thread_fun(void *param);


int main(){
    int n = 10;//pick a number
    Barrier my_barrier(n);
    pthread_t thread[n];
    for(int i = 0; i < n; i++){
        if(pthread_create(&thread[i],NULL,thread_fun,&my_barrier)  !=0 ){
            cerr << "failed to create thread: " << endl;
            return 1;
        }
    }

    for(int i = 0; i< n; i++){
        if(pthread_join(thread[i],NULL) !=0 ){
            cerr << "failed to join thread: " << endl;
            return 1;
        }
    }


    


    return 0;
}

Barrier::Barrier( int n ){
    num_threads = n;
    counter = 0;
    pthread_mutex_init(&mtx,nullptr);
    pthread_cond_init(&cond_var,nullptr);
}
Barrier::~Barrier(){
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond_var);

}

void Barrier::wait() {
    pthread_mutex_lock(&mtx);
    counter++;
    if (counter < num_threads) {
        cout << "Thread waiting" << endl;
        pthread_cond_wait(&cond_var, &mtx);
    } else {
        pthread_cond_broadcast(&cond_var);
    }
    pthread_mutex_unlock(&mtx);
}

void* thread_fun(void *param){
    Barrier* barrier = static_cast<Barrier*>(param);
    cout << "Thread reached barrier\n";
    barrier->wait();
    cout << "Thread passed barrier\n";
    return nullptr;
}
