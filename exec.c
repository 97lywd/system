/*
 * exec函数族接口的使用
 */


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


int main()
{
  printf("hello\n");
  execlp("ls","ls","-l",NULL);
 // execl("/bin/ls","ls","-l",NULL);
  return 0;
}
 
