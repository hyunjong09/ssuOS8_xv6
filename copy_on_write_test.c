#include "types.h"
#include "stat.h"
#include "user.h"

int memory = 0;

int main(int argc, char* argv[]) {
    printf(1, "before fork\n");
    printf(1, "number of free pages: %d\n\n", getNumFreePages());

    if (fork() == 0) {
        printf(1, "hi, i'm child process\n");
        printf(1, "before write, number of free pages: %d\n", getNumFreePages());
        memory = 3;
        printf(1, "after write, number of free pages: %d\n", getNumFreePages());
        printf(1, "bye\n");

        return 0;
    }

    while (1);

    return 0;
}