#include "types.h"
#include "stat.h"
#include "user.h"
#include "memlayout.h"  // PGSIZE를 포함하기 위해 추가

void allocate_new_page_test() {
    char *heap_pointer;
    int i;

    printf(1, "Starting allocate new page test\n");

    // 현재 힙 포인터를 가져옵니다.
    heap_pointer = (char*)sbrk(0);

    // sbrk를 사용하여 새로운 메모리를 할당합니다.
    // 이는 페이지 폴트를 발생시키고 새로운 페이지를 할당하게 합니다.
    sbrk(2 * PGSIZE); // 8KB 할당

    // 할당된 메모리의 끝부분에 접근하여 페이지 폴트를 유도합니다.
    // 힙 포인터에서 8KB 위치에 접근하여 페이지 폴트를 유도합니다.
    char *fault_address = heap_pointer + 2 * PGSIZE - 1;

    printf(1, "Accessing address: %p to cause page fault\n", fault_address);

    // 접근 시도: 페이지 폴트가 발생하여 새로운 페이지가 할당되어야 합니다.
    *fault_address = 'a';

    printf(1, "Access to address %p succeeded, new page allocated\n", fault_address);
}

int main(int argc, char *argv[]) {
    allocate_new_page_test();
    exit();
}
