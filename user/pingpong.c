#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipe1[2];  // Pipe for parent -> child (ping)
  int pipe2[2];  // Pipe for child -> parent (pong)

  // Create two pipes
  if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
      exit(1);
  }

  // Fork to create a child process
  int pid = fork();

  if (pid < 0) {
    exit(1);
  }

  if (pid == 0) {  // Child process
    // Close unnecessary ends of the pipes
    close(pipe1[1]); // Close write end of pipe1
    close(pipe2[0]); // Close read end of pipe2

    // Read the byte from parent
    char byte;
    read(pipe1[0], &byte, 1);
    close(pipe1[0]); // Close read end after reading

    // Print message for received ping
    printf("%d: received ping\n", getpid());

    // Send the byte back to the parent
    write(pipe2[1], &byte, 1);
    close(pipe2[1]); // Close write end after writing

    // Child exits
    exit(0);
  } else {  // Parent process
    // Close unnecessary ends of the pipes
    close(pipe1[0]); // Close read end of pipe1
    close(pipe2[1]); // Close write end of pipe2

    // Send a byte to the child
    char byte = 'x';
    write(pipe1[1], &byte, 1);
    close(pipe1[1]); // Close write end after writing

    // Read the byte from the child
    read(pipe2[0], &byte, 1);
    close(pipe2[0]); // Close read end after reading

    // Print message for received pong
    printf("%d: received pong\n", getpid());

    // Wait for the child process to finish
    int child_pid;
    wait(&child_pid);

    // Parent exits
    exit(0);
  }
}