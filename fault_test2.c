#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PGSIZE 4096

void test_address(char *addr);

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    printf(1, "Usage: pagefault_test <address>\n");
    exit();
  }

  uint addr = atoi(argv[1]);

  // 주소를 테스트합니다.
  test_address((char*)addr);

  exit();
}

void test_address(char *addr)
{
  printf(1, "Accessing address: 0x%x\n", addr);

  // 주소에 접근하여 페이지 폴트를 유발하거나 정상적으로 접근합니다.
  *addr = 'A';

  // 페이지 폴트가 처리된 후 정상적으로 실행됩니다.
  printf(1, "Value at address: %c\n", *addr);
  printf(1, "This line should be printed.\n");
}
