#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "memlayout.h"

void test_address(char *addr, char value);

int
main(int argc, char *argv[])
{
  char *valid_addr = sbrk(PGSIZE * 2); // 2 페이지 크기만큼 메모리를 할당합니다.
  char *page_fault_addr = valid_addr + (PGSIZE * 3);  // 할당된 메모리 영역 바로 밖의 주소를 설정합니다.
  char *invalid_addr = (char*)0x80000000; // 커널 공간의 주소를 사용해 페이지 폴트를 유발합니다.

  // 유효한 주소 테스트
  printf(1, "Testing valid address:\n");
  test_address(valid_addr, 'V');

  // 페이지 폴트를 유발하는 유효한 주소 테스트
  printf(1, "Testing page fault address:\n");
  test_address(page_fault_addr, 'F');

  // 유효하지 않은 주소 테스트
  printf(1, "Testing invalid address:\n");
  test_address(invalid_addr, 'I');

  exit();
}

void test_address(char *addr, char value)
{
  printf(1, "Accessing address: 0x%x\n", addr);

  // 주소에 접근하여 페이지 폴트를 유발하거나 정상적으로 접근합니다.
  *addr = value;

  // 페이지 폴트가 처리된 후 정상적으로 실행됩니다.
  printf(1, "Value at address: %c\n", *addr);
  printf(1, "If This line is printed Memory allocate Success.\n\n");
}
