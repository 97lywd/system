#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  while(1){
     printf("[lywd@localhost]");
     fflush(stdout);
     char buff[1024] = {0};
    if(scanf("%[^\n]%*c",buff) != 1){
      getchar();
      continue;
    }  //遇到\n结束
     char* argv[32];
     int argc = 0;
     char* ptr = buff;
     while(*ptr != '\0'){
        if(!isspace(*ptr++)){
          //当前位置不是空白字符
          argv[argc++] = ptr;
          while(!isspace(*ptr) && *ptr != '\0'){
            ptr++;
          }
        }
        *ptr = '\0';
        ptr++;
     }
     argv[argc] = NULL;
     if(strcmp(argv[0],"cd") == 0){
        //该变当前工作路径
        chdir(argv[1]);
        continue;
     }
     //创建子进程 执行其他任务
     int pid = fork();
     if(pid < 0){
        continue;
     }else if(pid == 0){
       if(execv("./",argv[0]) < 0){
         perror("exec error");
       }
        //替换失败退出
        exit(0);
     }
     //等待子进程退出
     wait(NULL);
  }
  return 0;
}
