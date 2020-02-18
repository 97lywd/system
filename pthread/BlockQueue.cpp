#include<iostream>
#include<queue>
#include<cstdlib>
#include<pthread.h>
#define NUM 10
class BlockQueue{
    private:
        std::queue<int> q;
        int _capacity;
        pthread_mutex_t _lock;
        pthread_cond_t _full;
        pthread_cond_t _empty;
    private:
        void LockQueue(){
            pthread_mutex_lock(&_lock);
        }
        void UnlockQueue(){
            pthread_mutex_unlock(&_lock);
        }
        void ProductWait(){
            pthread_cond_wait(&_full,&_lock);
        }
        void ConsumeWait(){
            pthread_cond_wait(&_empty,&_lock);
        }
        void SigProduct(){
            pthread_cond_signal(&_full);
        }
        void SigConsume(){
            pthread_cond_signal(&_empty);
        }
        bool IsEmpty(){
            return (q.size() == 0 ? true : false);
        }
        bool IsFull(){
            return (q.size() == _capacity ? true : false);
        }
    public:
        BlockQueue(int cap = NUM):_capacity(cap){
            pthread_mutex_init(&_lock,NULL);
            pthread_cond_init(&_full,NULL);
            pthread_cond_init(&_empty,NULL);
        }
        void PushData(const int &data){
            LockQueue();
            while(IsFull()){
                SigConsume();
                std::cout << "queue full, stop producting" << std::endl;
                ProductWait();
            }
            q.push(data);
            UnlockQueue();
        }
        void PopData(int &data){
            LockQueue();
            while(IsEmpty()){
                SigProduct();
                std::cout << "queue empty,please product data" << std::endl;
                ConsumeWait();
            }
            data = q.front();
            q.pop();
            UnlockQueue();
        }
        ~BlockQueue(){
            pthread_mutex_destroy(&_lock);
            pthread_cond_destroy(&_full);
            pthread_cond_destroy(&_empty);
        }
};



void *cunsumer(void *arg){
    BlockQueue *bq = (BlockQueue*)arg;
    int data;
    while(1){
        bq->PopData(data);
        std::cout << "Consume data :" << data << std::endl;
    }
}

void *producer(void *arg){
    BlockQueue *bq = (BlockQueue*)arg;
    srand((unsigned long)time(NULL));
    while(1){
        int data = rand() % 1024;
        bq->PushData(data);
        std::cout << "Product data : " << data << std::endl;
    }
}


int main()
{
    BlockQueue bq;
    pthread_t c,p;
    pthread_create(&p,NULL,producer,(void*)&bq);
    pthread_create(&c,NULL,cunsumer,(void*)&bq);
    pthread_join(p,NULL);
    pthread_join(c,NULL);
    return 0;
}
