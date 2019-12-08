#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
void sigcb(int signo)
{
    while(waitpid(-1,NULL,0) > 0);
}
int main()
{
    signal(SIGCHLD,sigcb);
    pid_t pid = fork();
    if(pid == 0){
        sleep(5);
        exit(0);
    }
    while(1){
        printf("-------------\n");
        sleep(1);
    }
    return 0;
}
