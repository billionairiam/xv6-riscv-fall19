#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    // ANSI escape code to clear the terminal
    printf("\033[2J\033[H");

    exit(0);
}
