#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  char err_msg[] = "too few args!\n";
  if(argc != 2){
    write(2, err_msg, strlen(err_msg));
    exit();
  }
  //  string to integer
  int sleepTime = atoi(argv[1]);
  sleep(sleepTime);  
  exit();
}
