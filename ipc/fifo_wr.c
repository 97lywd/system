
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/sdt.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
int main()
{
    umask(0);
    char *file = "./test.fifo";
    int ret = mkfifo(file,0664);
    if(ret < 0 && errno != EEXIST){
        
        perror("mkfifo error");
        return -1;
    }
    int fd = open(file,O_WRONLY);
    if(fd < 0){
        perror("open error");
        return -1;
    }
    while(1){
        char buff[1024] = {0};
        scanf("%s",buff);
        ret = write(fd,buff,strlen(buff));
        if(ret < 0){
            perror("write error");
            return -1;
        }
    }
    close(fd);
    return 0;
}
