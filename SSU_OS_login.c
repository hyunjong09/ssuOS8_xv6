#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define INPUT_BUFFER 32
#define MAX_ACCOUNT 10

char userID[MAX_ACCOUNT][INPUT_BUFFER];
char pwdID[MAX_ACCOUNT][INPUT_BUFFER];
int acc_cnt = 0;
int stop_flag = 0;

void parse_word(int fd, char *dest)
{
  for (int j = 0;; j++)
  {
    if (read(fd, &dest[j], 1) <= 0) {
      stop_flag = 1;
      break;
    }
    if (dest[j] == ' ' || dest[j] == '\n') {
      dest[j] = '\0';
      break;
    }
  }
}

void get_user_list()
{
  int fd;

  fd = open("list.txt", O_RDONLY);
  if (fd < 0)
  {
    printf(1, "opening list.txt has been error\n");
    exit();
  }

  for (int i = 0; i < MAX_ACCOUNT; i++)
  {
    if(stop_flag)
      break;
    acc_cnt++;
    parse_word(fd, userID[i]);
    parse_word(fd, pwdID[i]);
  }
  close(fd);
}

int check_idpw()
{
  char id[INPUT_BUFFER]={0,}, pw[INPUT_BUFFER] = {0, };

  printf(1, "Username: ");
  parse_word(0, id); 
  printf(1, "Password: ");
  parse_word(0, pw);

  for (int i = 0; i < acc_cnt; i++)
  {
    if (!strcmp(id, userID[i]))
    {
      if (!strcmp(pw, pwdID[i]))
      {
        return 1;
      }
      return 0;
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  int pid, wpid;
  get_user_list();

  while (1)
  {
    if (check_idpw())
      for (;;)
      {
        printf(1, "init: starting sh\n");
        pid = fork();
        if (pid < 0)
        {
          printf(1, "init: fork failed\n");
          exit();
        }
        if (pid == 0)
        {
          exec("sh", argv);
          printf(1, "init: exec sh failed\n");
          exit();
        }
        while ((wpid = wait()) >= 0 && wpid != pid)
          printf(1, "zombie!\n");
      }
  }
}