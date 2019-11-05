

/*
 *
 * 这个demo演示线程退出返回值的获取
 *
 */
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void *thr_start(void *arg)
{
   sleep(5);
   return "hello";
}
int main()
{
  pthread_t tid;
  int ret = pthread_create(&tid,NULL,thr_start,NULL);
  if(ret != 0){
    printf("create thread error\n");
    return -1;
  }
  void *retval; 
  pthread_join(tid,&retval);  //阻塞函数
  printf("thread exit val:%s\n",(char*)retval);
  return 0;
}
