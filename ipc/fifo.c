/*
 *
 *     命名管道操作
 *    打开特性：若管道文件以只读的方式打开，则会阻塞，直到这个文件被以写的方式打开
 *              若管道文件以只写的方式打开，则会阻塞，直到这个文件被以读的方式打开
 *
 */


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/sdt.h>
#include<fcntl.h>
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
    int fd = open(file,O_RDONLY);
    if(fd < 0){
        perror("open error");
        return -1;
    }
    while(1){
        char buff[1024] = {0};
        ret = read(fd,buff,1023);
        if(ret < 0){
            perror("read error");
            return -1;
        }
            printf("buff :[%s]\n",buff);
    }
    close(fd);
    return 0;
}
