#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



int main(int argc , char* argv[]){
    int parent_fd[2];
    pipe(parent_fd);
     int p = 1;
    int pid = fork();
    if (pid > 0){  
      for(int i =2;i<35;i++){
        int tmp = i;
        write(parent_fd[1],&tmp,sizeof(tmp));
      }
      close(parent_fd[0]);
    }else if (pid ==0){
      int  fd = parent_fd[0];
      for (;;){        
       p++;
      int buf;
      int childpipe_fd[2];
     int n =  read(fd,&buf,sizeof(buf));
     if (n != sizeof(buf)){
       break;
     }
     printf("%d,%d\n",buf,getpid());
     pipe(childpipe_fd);
      int childpid = fork();
       if (childpid==0){
       for(;;){
        int n = read(fd,&buf,sizeof(buf));
        // printf("%d\n",buf);

        if(n != sizeof(buf)){
          close(childpipe_fd[1]);
          break;
          }
         int temp2 = buf;
        if ((temp2 % p) != 0) {
          // printf("buf:%d,%d\n",buf,getpid());
          // sleep(2);
            write(childpipe_fd[1],&temp2,sizeof(temp2));
          }
       } 
       }else if (childpid>0){
         fd = childpipe_fd[0];
       } 
    }
}
  exit();
}
