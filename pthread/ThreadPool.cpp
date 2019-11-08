/*
 * 线程池的实现：线程安全的任务队列+线程
 * 任务类：
 *    class MyTask{}
 * 线程池类：
 *    class ThreadPool{}
 */

#include <iostream>
#include<sstream>
#include<thread>
#include<queue>
#include<vector>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define MAX_THREAD 5
#define MAX_QUEUE 10
typedef void(*handler_t)(int);
class MyTask{
    private:
        int _data;
        handler_t _handler;
    public:
        MyTask(int data,handler_t handle)
        :_data(data),_handler(handle) {}

        void SetTask(int data,handler_t handle){
          _data = data;
          _handler = handle;
          return;
        }
        void Run(){
          return _handler(_data);
        }
};



class ThreadPool{
    private:
        std::queue<MyTask> _queue;
        int _capacity;
        pthread_mutex_t _mutex;
        pthread_cond_t _cond_pro;
        pthread_cond_t _cond_con;
        int _thr_max;
        std::vector<std::thread> _thr_list;
    private:
         void thr_start(){
            pthread_mutex_lock(&_mutex);
            while(_queue.empty()){
                pthread_cond_wait(&_cond_con,&_mutex);
            }
            MyTask tt = _queue.front();
            _queue.pop();
            pthread_mutex_unlock(&_mutex);
            pthread_cond_signal(&_cond_pro);
            tt.Run();
            return;
        }
    public:
        ThreadPool(int maxq = MAX_QUEUE, int maxt = MAX_THREAD)
          :_capacity(maxq),_thr_max(maxt),_thr_list(maxt){
            pthread_mutex_init(&_mutex,NULL);
            pthread_cond_init(&_cond_con,NULL);
            pthread_cond_init(&_cond_pro,NULL);
          }
        ~ThreadPool(){
            pthread_cond_destroy(&_cond_con);
            pthread_cond_destroy(&_cond_pro);
            pthread_mutex_destroy(&_mutex);
        }
        bool PoolInit(){
            for(int i = 0; i < _thr_max; i++){
                _thr_list[i] = std::thread(&ThreadPool::thr_start,this);
            }
            return true;
        }
        bool AddTask(MyTask &tt){
            pthread_mutex_lock(&_mutex);
            while(_queue.size() == _capacity){
                pthread_cond_wait(&_cond_pro,&_mutex);
            }
            _queue.push(tt);
            pthread_mutex_unlock(&_mutex);
            pthread_cond_signal(&_cond_con);
            return true;
        } 
};




void test(int data){
    srand(time(NULL));
    int nsec = rand() % 5;
    std::stringstream ss;
    ss << "thread:" << pthread_self << "processing data";
    ss << data << " and sleep " << nsec << "sec\n";
    std::cout << ss.str();
    sleep(nsec);
    return;
}


int main(){
  ThreadPool pool;
  pool.PoolInit();
  for(int i = 0; i < 10; i++){
      MyTask tt(i,test);
      pool.AddTask(tt);
  }
  while(1){
    sleep(1);
  }
  return 0;
}
