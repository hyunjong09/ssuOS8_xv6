#include "types.h"
#include "stat.h"
#include "user.h"
#include "memlayout.h"

void stack_expand_test() {
    int stack_size = 0;
    char *stack_pointer;
    
    printf(1, "Starting stack expand test\n");

    // Allocate memory on the stack in small increments to force stack expansion
    for (int i = 0; i < 10; i++) {
        stack_size += 4096; // 4KB
        stack_pointer = (char *)malloc(stack_size);
        if (stack_pointer == 0) {
            printf(1, "Failed to allocate memory on the stack\n");
            exit();
        }
        printf(1, "Allocated %d bytes on the stack\n", stack_size);
    }

    // Access the newly allocated stack memory to force page fault handling
    for (int i = 0; i < stack_size; i += 4096) {
        stack_pointer[i] = 'a';
    }

    printf(1, "Stack expand test completed successfully\n");
}

void pagefault_test() {
    char *valid_addr = sbrk(PGSIZE * 2); // Allocate 2 pages
    char *page_fault_addr = valid_addr + (PGSIZE * 3);  // Address just outside allocated memory

    printf(1, "Starting pagefault test\n");

    // Access invalid memory to trigger a page fault
    printf(1, "Accessing invalid memory address: %p\n", page_fault_addr);
    *page_fault_addr = 'a';

    printf(1, "Pagefault test did not trigger as expected\n");
}

int main(int argc, char *argv[]) {
    stack_expand_test();
    pagefault_test();
    exit();
}
