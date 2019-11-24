

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    int pid1 = fork();
    if(ret < 0){
        perror("pipe error");
        return -1;
    } 
    if(pid1 == 0){
        dup2(pipefd[1],1);
        execl("/bin/ps","ps","-ef",NULL);
        exit(0);
    }
    int pid2 = fork();
    if(pid2 == 0){
        dup2(pipefd[0],0);
        //close(pipefd[1]);
        execl("/bin/grep","grep","sshd",NULL);
        exit(0);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid1,NULL,0);
    return 0;
}
