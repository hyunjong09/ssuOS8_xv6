#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096

void
test_pagefault_handler()
{
  char *stack;
  int i;

  // 스택의 하위 주소로 접근하여 페이지 폴트를 유도합니다.
  for(i = 1; i <= 20; i++) {
    stack = (char *) (KERNBASE - (i * PGSIZE)); // KERNBASE는 커널과 사용자 공간을 구분하는 기준 주소입니다.
    printf(1, "Accessing stack address: %p\n", stack);
    *stack = 0; // 페이지 폴트 유도
  }

  printf(1, "Test completed.\n");
}

int
main(int argc, char *argv[])
{
  test_pagefault_handler();
  exit();
}