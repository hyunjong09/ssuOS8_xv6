#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PGSIZE 4096

int
main(int argc, char *argv[])
{
  char *invalid_addr = (char*)(0x80000000);  // 커널 공간의 주소를 사용해 페이지 폴트를 유발합니다.
  printf(1, "Accessing invalid address: 0x%x\n", invalid_addr);
  
  // 다음 줄에서 페이지 폴트가 발생할 것입니다.
  printf(1, "Value at invalid address: %c\n", *invalid_addr);

  // 프로그램이 여기까지 도달하지 못할 것입니다.
  printf(1, "This line should not be printed.\n");
  
  exit();
}
