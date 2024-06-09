#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096

void test_page_fault() {
    // 페이지 폴트를 유발하기 위해 큰 배열 할당 및 접근
    char *buffer = (char*)sbrk(PGSIZE * 10); // 10 페이지 할당
    if (buffer == (char*)-1) {
        printf(1, "sbrk failed\n");
        return;
    }

    printf(1, "Buffer allocated at address: %p\n", buffer);
    printf(1, "Testing page fault handling...\n");

    for (int i = 0; i < PGSIZE * 10; i += PGSIZE) {
        buffer[i] = i / PGSIZE;
    }

    printf(1, "Page fault test completed successfully\n");
}

void test_stack_allocation() {
    char dummy;
    uint sp = (uint)&dummy;
    uint new_sp = sp - (PGSIZE * 4);  // 4 페이지 크기만큼 아래로 설정

    printf(1, "Current stack pointer: 0x%x\n", sp);
    printf(1, "Testing stack allocation...\n");

    // 스택을 확장하여 페이지 폴트를 유발
    for (char *ptr = (char*)(new_sp + PGSIZE); ptr < (char*)sp; ptr += PGSIZE) {
        printf(1, "Accessing stack address: %p\n", ptr);
        *(volatile char*)ptr = 0; // volatile을 사용하여 최적화 방지
    }

    printf(1, "Stack allocation test completed successfully\n");
}

int main(void) {
    test_page_fault();
    test_stack_allocation();
    exit();
}
