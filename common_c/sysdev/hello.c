# include <stdio.h>
# include <string.h>
# include <unistd.h>

/**
 * Run compiled script with strace
 */
int main(int argc, char *argv[])
{
    printf("Run strace on me!");
    char msg[] = "I'm using system call!";
    write(STDOUT_FILENO, msg, strlen(msg));
    return 0;
}
