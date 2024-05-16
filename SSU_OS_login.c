#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

/*
Function Declaration
*/
void get_user_list();
void parse_list();
int check_idpw();

/*
Variable Declaration
*/
char userID[16][32];
char pwdID[16][32];
int stop = 0;
int count = 0; 

void get_user_list(){
    int fd;

    // list.txt open
    fd = open("list.txt", O_RDONLY);
    if(fd < 0){
        printf(1, "open failed");
        exit();
    }

    // list.txt에 있는 [Username] [Password] 가져오기
    for(int i = 0; i < 10; i++){
        // 종료 조건
        if(stop){
            break;
        }
        count++;

        // save
        parse_list(fd, userID[i]);
        parse_list(fd, pwdID[i]);
    }
}

void parse_list(int fd, char *ID){
    for(int i = 0; ; i++){
        if(read(fd, &ID[i], 1) <= 0){
            stop = 1;
            break;
        }
        if(ID[i] == ' ' || ID[i] == '\\n'){
            ID[i] = '\\0';
            break;
        }
    }
}

int check_idpw(){
    char id[32] = {0, };
    char pw[32] = {0, };

    printf(1, "Username: ");
    parse_list(0, id);
    printf(1, "Password: ");
    parse_list(0, pw);

    for(int i = 0 ; i < count; i++){
        if(!strcmp(id, userID[i])){
            if(!strcmp(pw, pwdID[i])){
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int main(int argc, char *argv[]){
    int pid, wpid;
    get_user_list();

    while(1){
        if(check_idpw()){
            for(;;){
                printf(1, "init: starting sh\\n");
                pid = fork();
                if(pid < 0){
                    printf(1, "init: fork failid\\n");
                    exit();
                }
                if(pid == 0){
                    exec("sh", argv);
                    printf(1, "init: exec sh failed\\n");
                    exit();
                }
                while((wpid = wait()) >= 0 && wpid != pid){
                    printf(1, "zombie!\\n");
                }

            }
        }
    }
}