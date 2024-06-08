#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BSIZE 512
#define NINDIRECT (BSIZE / sizeof(uint))
#define NDBLINDIRECT ((NINDIRECT) * (NINDIRECT))
#define NUM_BYTES ((NDBLINDIRECT) * (BSIZE))

#define NUM_TEST3 10

char buf[NUM_BYTES], buf2[NUM_BYTES];
char filename[16] = "test_file0";
const int len = 10;

void failed(const char *msg)
{
  printf(1, msg);
  printf(1, "Test failed!!\n");
  exit();
}

void test1(int first)
{
  int fd;

  if (first)
    printf(1, "Test 1: Write %d bytes\n", NUM_BYTES);
  fd = open(filename, O_CREATE | O_WRONLY);
  if (fd < 0)
    failed("File open error\n");
  if (write(fd, buf, NUM_BYTES) < 0)
    failed("File write error\n");
  if (close(fd) < 0)
    failed("File close error\n");
  if (first)
    printf(1, "Test 1 passed\n\n");
}

void test2(int first)
{
  int i, fd;
  for (i = 0; i < NUM_BYTES; i++)
    buf2[i] = 0;
  
  if (first)
    printf(1, "Test 2: Read %d bytes\n", NUM_BYTES);
  fd = open(filename, O_RDONLY);
  if (fd < 0)
    failed("File open error\n");
  if (read(fd, buf2, NUM_BYTES) < 0)
    failed("File read error\n");
  for (i = 0; i < NUM_BYTES; i++) {
    if (buf2[i] != (i % 26) + 'a') {
      printf(1, "%dth character, expected %c, found %c\n", i, (i % 26) + 'a', buf2[i]);
      failed("");
    }
  }
  if (close(fd) < 0)
    failed("File close error\n");
  if (unlink(filename) < 0)
    failed("File unlink error\n");
  if ((fd = open(filename, O_RDONLY)) >= 0)
      failed("File not erased\n");
  if (first)
    printf(1, "Test 2 passed\n\n");
}

int main(int argc, char *argv[])
{
  int i;
  for (i = 0; i < NUM_BYTES; i++)
    buf[i] = (i % 26) + 'a';

  test1(1);
  test2(1);

  printf(1, "Test 3: repeating test 1 & 2\n");
  for (i = 0; i < NUM_TEST3; i++)
  {
    printf(1, "Loop %d: ", i + 1);
    filename[len - 1] = (i % 10) + '0';
    printf(1, "1.. ");
    test1(0);
    printf(1, "2.. ");
    test2(0);
    printf(1, "ok\n");
  }
  printf(1, "Test 3 passed\n");
  
  printf(1, "All tests passed!!\n");
  exit();
}
