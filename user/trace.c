#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
  if (argc < 3) {
    fprintf(2, "Usage trace [mask]\n");
  }

  int mask = atoi(argv[1]);
  int ret = trace(mask);
  if (ret == -1)
    exit(-1);

  exec(argv[2], argv+2);
  exit(0);
}