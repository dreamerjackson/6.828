#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



int main(int argc , char* argv[]){

  int parent_fd[2];
  int child_fd[2];
  char buf[1];
   
  pipe(parent_fd);
  pipe(child_fd);
  int pid = fork();
  // parent
  if(pid>0){
       close(parent_fd[0]);
       close(child_fd[1]);
       write(parent_fd[1],"1",1);
       int n =  read(child_fd[0],buf,1);
      if(n == 1) {
         printf("recieve pong");
       }
    // child 
  }else if(pid == 0 ){
     close(parent_fd[1]);
    close(child_fd[0]);
    printf("child start\n");
     int pp =  read(parent_fd[0],buf,1);
     printf("int:%d\n",pp);
     if(pp == 1) {
         printf("recieve ping");
       }
      write(child_fd[1],"0",1);
    //
  }else{
    fprintf(2, "write error\en");
  }



  exit();
}
