#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// 判断两个字符是否相同
void
find(char *path,char *search)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n",path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    ;
    char fname[DIRSIZ+1];
    memset(fname,0,sizeof(fname));
    char *tmp;
    for(tmp=path+strlen(path); tmp>= path && *tmp != '/'; tmp--)
    ;
    tmp++;
    memmove(fname, tmp, strlen(tmp));
    //char *filename = fmtname(path);
    //   printf("%s,%s\n", filename,search);
    //      if (strcmp(path,"./b")==0){
    //      printf("yes,%s,%s!\n",fname,search);
    //  }

   int n = strcmp(fname,search);
   if (n == 0){
     printf("%s\n",path);
   }
   break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      // 现在p存储的是全路径
      if (strcmp(p,".")!=0 && strcmp(p,"..")!=0){
        //   printf("p:%s\n",buf);
        find(buf,search);
      }
    }
    break;
  }
  close(fd);
}



int
main(int argc, char *argv[])
{

  if(argc != 3){
    printf("args param !=2 \n");
    exit();
  }
  find(argv[1],argv[2]);
  exit();
}
