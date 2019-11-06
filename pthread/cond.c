/*
 *
 *通过吃面的demo体会同步的思想
 *
 */
#include <stdio.h>
#include<unistd.h>
#include<pthread.h>
int noodles = 0; //默认没有noddles
pthread_cond_t cond_foodie;
pthread_cond_t cond_chef;
pthread_mutex_t mutex;
void* thr_chef(void* arg)
{
  while(1){
    //没有面则做面，有面没人吃则等待
    while(noodles == 1){
      pthread_cond_wait(&cond_chef,&mutex);
    pthread_mutex_lock(&mutex);
    }
    printf("master made a bow of noodles\n");
    noodles = 1;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond_foodie);
  }
  return NULL;
}
void* thr_foodie(void* arg)
{
  while(1){
    //有面吃面，没面则等待
    while(noodles == 0)
    {
      pthread_cond_wait(&cond_foodie,&mutex);
    pthread_mutex_lock(&mutex);
    }
    printf("have eat\n");
    noodles = 0;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond_chef);
  }
  return NULL;
}
int main()
{
  int ret,i;
  pthread_t ctid[4],etid[4];
  pthread_cond_init(&cond_foodie,NULL);
  pthread_cond_init(&cond_chef,NULL);
  pthread_mutex_init(&mutex,NULL);
  for(i = 0; i < 4; i++){
  ret = pthread_create(&ctid[i],NULL,thr_chef,NULL);
  if(ret != 0){
     printf("create error\n");
     return -1;
    }
  }
  for(i = 0; i < 4; i++){
  ret = pthread_create(&etid[i],NULL,thr_foodie,NULL);
  if(ret != 0){
     printf("create error\n");
     return -1;
      }
  }
  for(i = 0; i < 4; i++){

  pthread_join(ctid[i],NULL);
  pthread_join(etid[i],NULL);
  }

  pthread_cond_destroy(&cond_foodie);
  pthread_cond_destroy(&cond_chef);
  pthread_mutex_destroy(&mutex);
  return 0;
}
