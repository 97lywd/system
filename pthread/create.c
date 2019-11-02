#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void *thr_start(void *arg)
{
   while(1)
   {
     pthread_t tid = pthread_self();
     printf("---odniary-----%s-%lu\n",(char*)arg,tid);
     sleep(1);
   }
  return NULL;
}
int main()
{
  int ret;
  pthread_t tid;
  pthread_t mtid = pthread_self();
  ret = pthread_create(&tid,NULL,thr_start,(void*)"hello");
  if(ret != 0)
  {
    printf("thread create error\n");
    return -1;
  }
  while(1)
  {
    printf("--------main-----------mtid:%lu----ctid:%lu\n",mtid,tid);
    sleep(1);
  }
  return 0;
}
