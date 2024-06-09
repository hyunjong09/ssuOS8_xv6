#include "types.h"
#include "stat.h"
#include "user.h"
#include "memlayout.h"  // PGSIZE를 포함하기 위해 추가

void allocate_new_page_test() {
    volatile char dummy[PGSIZE * 4];  // 스택을 확장하기 위해 더미 배열 선언

    printf(1, "Starting allocate new page test\n");

    // 스택 포인터를 가져옵니다.
    char *stack_pointer = (char*) &dummy[PGSIZE * 4 - 1];

    // 스택 포인터를 조금 낮춰서 페이지 폴트를 유도합니다.
    char *fault_address = stack_pointer - 3 * PGSIZE; // 현재 스택 포인터보다 12KB 아래

    printf(1, "Accessing address: %p to cause page fault\n", fault_address);

    // 접근 시도: 페이지 폴트가 발생하여 새로운 페이지가 할당되어야 합니다.
    *fault_address = 'a';

    printf(1, "Access to address %p succeeded, new page allocated\n", fault_address);
}

int main(int argc, char *argv[]) {
    allocate_new_page_test();
    exit();
}
