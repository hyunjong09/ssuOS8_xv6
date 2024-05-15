#include "types.h"
#include "stat.h"
#include "user.h"

char buf[1];
int endLine;
// test
void
hcat(int fd)
{
  int n;
  int cntLine =0; //current Line

    while((n = read(fd, buf, sizeof(buf))) > 0) {
      if (write(1, buf, n) != n) {
        printf(1, "cat: write error\n");
        exit();
      }
    if(buf[0] == '\n'){
      cntLine++;
      if(cntLine == endLine){
        break;
      }
    }
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 2){ //1->2 modify(argument)
    hcat(0);
    exit();
  }

  endLine = atoi(argv[1]);
  
  for(i = 2; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    hcat(fd);
    close(fd);
  }
  exit();
}
