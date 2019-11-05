
/*
 *
 *黄牛抢票的demo 模拟线程不安全
 *
 */
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
int ticket = 100;
pthread_mutex_t mutex;
void *ticket_scalper(void *arg)
{
  int id = (int*)arg;
   while(1)
   {
     //互斥锁保护的是临界资源，加锁放在临界操作之前
     //阻塞加锁----无法加锁挂起等待
     //非阻塞加锁 -- 无法加锁则立即报错返回
     pthread_mutex_lock(&mutex);
      if(ticket > 0){
        printf("scalper:%d --- get ticket:%d\n",id,ticket);
        ticket--;
      }
      else{
      pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
      }
      pthread_mutex_unlock(&mutex);
   }
  return NULL;
}
int main()
{
  int i,ret;
  pthread_t tid[4];
  pthread_mutex_init(&mutex,NULL);
  for(i = 0; i < 4; i++)
 {
      ret = pthread_create(&tid[i],NULL,ticket_scalper,(void*)i);
      if(ret != 0){
        printf("create falied!!\n");
        return -1;
      }
 }
  for(i = 0; i < 4; i++)
  {
    pthread_join(tid[i],NULL);
  }
  pthread_mutex_destroy(&mutex);
  return 0;
}
