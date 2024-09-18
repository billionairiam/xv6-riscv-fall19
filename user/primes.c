#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
primes(int* nums)
{
  if (nums[0] != -1) {
    printf("prime %d\n", nums[0]);
    int new_nums[34] = { -1 };
    int index = 0;
    for (int i = 1; i < 34; i++) {
      if (nums[i] % nums[0] != 0 && nums[i] != -1) {
        new_nums[index] = nums[i];
        index++;
      }
    }

    int pipe1[2];
    if (pipe(pipe1) == -1) {
      exit(1);
    }

    int pid = fork();
    if (pid == 0) {
      int receive_num[34] = {-1};
      close(pipe1[1]);
      read(pipe1[0], receive_num, 34);
      close(pipe1[0]);

      primes(receive_num);
      exit(0);
    } else if (pid > 0)
    {
      close(pipe1[0]);
      write(pipe1[1], new_nums, 34);
      close(pipe1[1]);

      wait(0);
      exit(0);
    } else {
      printf("fork failed!\n");
      exit(-1);
    }
  } else {
    exit(0);
  }
}

int
main(int argc, char *argv[])
{
  int nums[34] = {-1};
  for (int i = 0; i < 34; i++) {
    nums[i] = i + 2;
  }

  primes(nums);
  exit(0);
}
