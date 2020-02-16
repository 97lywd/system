#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
    umask(0); 
    char *file = "./test.txt";
    if(mkfifo(file,0664) < 0){
        perror("mkfifo error");
    }
    int fd = open(file,O_RDONLY);
    if(fd < 0){
        perror("open fifo");
    }
    char buff[1024];
    while(1){
        buff[0] = 0;
        printf("-----\n");
        ssize_t s = read(fd,buff,sizeof(buff) - 1);
        if(s > 0){
            buff[s - 1] = 0;
            printf("it say--- %s\n",buff);
        }else if(s == 0){
            printf("exit\n");
            break;
        }else{
            perror("read error");
        }
    }
    close(fd);
    return 0;
}
