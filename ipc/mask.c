#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


void sigcb(int signum)
{
    printf("recv a signal:%d\n",signum);
}
int main()
{
    signal(SIGINT,sigcb);
    signal(40,sigcb);
    sigset_t set,old;
    sigemptyset(&set);   //清空信号集合
    sigemptyset(&old);
    sigfillset(&set);    //将所有信号都添加到set集合
    sigprocmask(SIG_BLOCK,&set,&old);  //阻塞所有信号
    printf("enter to continue\n");
    getchar();
    sigprocmask(SIG_UNBLOCK,&set,NULL); //解除阻塞
    return 0;
}
