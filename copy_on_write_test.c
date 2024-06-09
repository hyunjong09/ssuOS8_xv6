#include "types.h"
#include "stat.h"
#include "user.h"

int memory = 0;

int main(int argc, char* argv[]) {
    printf(1, "before fork\n");
  int num_free_pages_before = getNumFreePages();
    printf(1, "number of free pages: %d\n\n", num_free_pages_before);

    if (fork() == 0) {
        printf(1, "hi, i'm child process\n");
        int num_free_pages_before_write = getNumFreePages();
        printf(1, "before write, number of free pages: %d\n", num_free_pages_before_write);
        memory = 3;
        char *ptr = sbrk(0);
        ptr[0] = 'A';  // This should trigger a page fault and COW
        int num_free_pages_after_write = getNumFreePages();
        printf(1, "after write, number of free pages: %d\n", num_free_pages_after_write);
        printf(1, "bye\n");

        return 0;
    }

    while (1);

    return 0;
    