/*
 * 进程终止demo
 */


#include<stdio.h>
#include<unistd.h>

int main()
{
  printf("hello world");
  sleep(3);
  _exit(0);
  return 0;
}
