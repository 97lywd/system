
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/sdt.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
int main()
{
    char *file = "./test.txt";
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
    char buff[1024];
    while(1){
        buff[0] = 0;
        fflush(stdout);
        ssize_t s = read(0,buff,sizeof(buff) - 1);
        if(s > 0){
           buff[s] = 0;
           write(fd,buff,strlen(buff));
        }else if(s <= 0){
            perror("read error");
        }
        }
    close(fd);
    return 0;
}
