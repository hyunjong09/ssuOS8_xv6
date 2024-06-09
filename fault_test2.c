#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PGSIZE 4096

int
main(int argc, char *argv[])
{
  char *valid_addr = sbrk(PGSIZE * 2); // 2 페이지 크기만큼 메모리를 할당합니다.
  char *invalid_addr = valid_addr + (PGSIZE * 3);  // 할당된 메모리 영역 밖의 주소를 설정합니다.

  printf(1, "Accessing valid address: 0x%x\n", valid_addr);
  valid_addr[0] = 'A';  // 정상적인 접근

  printf(1, "Accessing invalid address: 0x%x\n", invalid_addr);
  *invalid_addr = 'B';  // 페이지 폴트를 유발합니다.

  // 페이지 폴트 후 정상적으로 실행될 것입니다.
  printf(1, "Value at invalid address: %c\n", *invalid_addr);
  printf(1, "This line should be printed.\n");

  exit();
}
