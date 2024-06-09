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
    stack = (char *) (4096 * 1024 - (i * PGSIZE)); // 4MB 영역의 상위 주소부터 접근
    printf(1, "Accessing stack address: %p\n", stack);
    *stack = 0; // 페이지 폴트 유도
    printf(1, "Successfully accessed address: %p\n", stack);
  }

  printf(1, "Test completed.\n");
}

int
main(int argc, char *argv[])
{
  test_pagefault_handler();
  exit();
}
