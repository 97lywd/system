

/*
 *
 *  体会匿名管道的操作及特性
 *
 */


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int pipefd[2] = {0};
    int ret = pipe(pipefd);
    int pid = fork();
    if(ret < 0){
        perror("pipe error");
        return -1;
    }
    if(pid < 0){
        perror("fork error");
        return -1;
    }else if(pid == 0){
        char buff[1024] = {0};
        int ret = read(pipefd[0],buff,1023);
        printf("buff:[%s] - [%d]\n",buff,ret);
    }else{
        char *ptr = "hello friend ~~";
        write(pipefd[1],ptr,strlen(ptr));
        sleep(1);
    }
    while(1){
        printf("-----------%d\n",getpid());
        sleep(1);
    }
    return 0;
}
