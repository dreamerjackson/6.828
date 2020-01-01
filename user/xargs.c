#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"



char *argv[5];

int
read_line(char *line)
{
  char buf;
  int count = 0;
  while(read(0, &buf, sizeof(buf)) == sizeof(buf) && buf != '\n') {
    *line++ = buf;
    count++;
  }
  *line = '\0';
  return count;
}




int
main(int argc, char *argv[])
{
  if (argc < 2){
    printf("wrong param\n");
    exit();
    }
    char line[50];
    memset(line,0,sizeof(line));
    while(read_line(line) != 0 ){
      char * arg[MAXARG];
      char** p;
      memset(arg,0,sizeof(arg));
      p = arg;
      for(int i = 1;i< argc;i++){
        *p++ = argv[i];
      }
      *p++ = line;
      // printf("line:%s\n",line);
      int pid;
      // for(int i = 0;i<5;i++){
      //  printf("arg %s\n", arg[i]);
      // }
      // printf("argv[1] %s\n",argv[1]);
      if ((pid = fork() ) == 0){
        //printf("%s,%s\n", );
        exec(argv[1], arg);
      }
      wait();
    }
  exit();
}
