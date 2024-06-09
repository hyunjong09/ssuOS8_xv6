// copy_on_write_test.c

#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
  printf(1, "before fork\n");
  int num_free_pages_before = get_num_free_pages();
  printf(1, "number of free pages: %d\n", num_free_pages_before);

  int pid = fork();

  if (pid < 0) {
    printf(1, "fork failed\n");
    exit();
  } else if (pid == 0) {
    // Child process
    printf(1, "hi, i'm child process\n");
    int num_free_pages_before_write = get_num_free_pages();
    printf(1, "before write, number of free pages: %d\n", num_free_pages_before_write);

    // Trigger copy-on-write
    char *ptr = sbrk(0);
    ptr[0] = 'A';  // This should trigger a page fault and COW

    int num_free_pages_after_write = get_num_free_pages();
    printf(1, "after write, number of free pages: %d\n", num_free_pages_after_write);
    printf(1, "bye\n");
  } else {
    // Parent process
    wait();
  }

  exit();
}
