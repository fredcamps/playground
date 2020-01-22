#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int pid = fork();
  char *args[3];
  if (pid == 0) {
    printf("Parent id: %d, Child id: %d \n", getpid(), pid);
    sleep(10);
    execv("./out.o", args);
    // wait(NULL);
  } else {
    args[0] = "hello.c";
    args[1] = "-o";
    args[2] = "out.o";
    printf("PID %d, Parent id: %d, Child id: %d \n", pid, getppid(), getpid());
    execv("/usr/bin/gcc", args);
    wait(NULL);
  }
  return 0;
}
