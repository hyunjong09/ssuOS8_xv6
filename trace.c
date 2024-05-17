#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
    int pid;
    int mask = atoi(argv[1]);
    int flag;
    int wpid;

    // argv 초기화
    char *tmpArgv[argc-2];
    int idx = 0;
    for(int i = 2 ; i < argc; i++){
        tmpArgv[idx++] = argv[i];
    }

    pid = fork();
    if(pid < 0){
        printf(1, "init: fork failid\n");
        exit();
    }
    if(pid == 0){
        flag = trace(mask);
        if(flag == 0){
            exec(tmpArgv[0], tmpArgv);
        }else{
         printf(1, "trace failed");
        }
        exit();
    }
    while((wpid = wait()) >= 0 && wpid != pid){
        printf(1, "zombie!\n");
    }
}