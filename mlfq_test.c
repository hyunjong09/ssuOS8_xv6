#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_CHILD 5
#define NUM_LOOP1 20000
#define NUM_LOOP2 50000
#define NUM_LOOP3 10000
#define NUM_LOOP4 25000

int me;

// ret: 0: child, 1: parent
int create_child(void) {
  for (int i = 0; i < NUM_CHILD; i++) {
    int pid = fork();
    if (pid == 0) {
      me = i;
      sleep(10);
      return 0;
    }
  }
  return 1;
}

void exit_child(int parent) {
  if (parent)
    while (wait() != -1); // wait for all child processes to finish
  else
    exit();
}

int main(int argc, char **argv) {
  int p; // is this parent?

  printf(1, "MLFQ test start\n");

  // Test 1
  printf(1, "\nFocused priority\n");

  p = create_child();

  if (!p) {
    int pid = getpid();
    int cnt[2] = {0};
    for (int i = 0; i < NUM_LOOP1; i++) {
      cnt[getlev()]++;
      setpriority(pid, me * 2);
    }
    printf(1, "process %d: L0=%d, L1=%d\n", pid, cnt[0], cnt[1]);
  }

  exit_child(p);

  // Test 2
  printf(1, "\nWithout priority manipulation\n");

  p = create_child();

  if (!p) {
    int pid = getpid();
    int cnt[2] = {0};
    for (int i = 0; i < NUM_LOOP2; i++)
      cnt[getlev()]++;
    printf(1, "process %d: L0=%d, L1=%d\n", pid, cnt[0], cnt[1]);
  }

  exit_child(p);

  // Test 3
  printf(1, "\nWith yield\n");

  p = create_child();

  if (!p) {
    int pid = getpid();
    int cnt[2] = {0};
    for (int i = 0; i < NUM_LOOP3; i++) {
      cnt[getlev()]++;
      yield();
    }
    printf(1, "process %d: L0=%d, L1=%d\n", pid, cnt[0], cnt[1]);
  }

  exit_child(p);

  // Test 4
  printf(1, "\nMonopolize\n");

  p = create_child();

  if (!p) {
    int pid = getpid();
    int cnt[2] = {0};
    if (me == NUM_CHILD - 1)
      monopolize(2024);
    for (int i = 0; i < NUM_LOOP4; i++)
      cnt[getlev()]++;
    printf(1, "process %d: L0=%d, L1=%d\n", pid, cnt[0], cnt[1]);
    if (me == NUM_CHILD - 1)
      monopolize(2024);
  }  

  exit_child(p);
  exit();
}
