#include "types.h"
#include "stat.h"
#include "user.h"

void allocate_new_page_test() {
    char *stack_pointer;

    printf(1, "Starting allocate new page test\n");

    // 현재 스택 포인터를 가져옵니다.
    stack_pointer = (char*)sbrk(0);

    // 스택 포인터 바로 아래의 페이지에 접근하여 페이지 폴트를 유도합니다.
    // 이는 페이지 폴트를 발생시키고 새로운 페이지를 할당하게 합니다.
    char *fault_address = stack_pointer - 2 * 4096; // 현재 스택 포인터보다 8KB 아래

    printf(1, "Accessing address: %p to cause page fault\n", fault_address);

    // 접근 시도: 페이지 폴트가 발생하여 새로운 페이지가 할당되어야 합니다.
    *fault_address = 'a';

    printf(1, "Access to address %p succeeded, new page allocated\n", fault_address);
}

int main(int argc, char *argv[]) {
    allocate_new_page_test();
    exit();
}