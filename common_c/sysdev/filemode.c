#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    int fd;
    int length = 50;
    char filename[] = "somefile.txt";
    char buffer[length];
    char *text = "1111";
    fd = open(filename, O_RDWR | O_CREAT, 0755);

    if (fd < 0) {
        printf("Error 0!\n");
        exit(1);
    }
    if (write(fd, text, strlen(buffer)) < 0) {
        printf("Error when write \n");
        exit(1);
    }
    if (read(fd, buffer, length) < 0) {
        printf("Fuck sakes!");
        exit(1);
    }

    char *another_text = "Hello my ball!";
    lseek(fd, 0, SEEK_END);
    if (write(fd, another_text, strlen(another_text)) < 0) {
        printf("Looser!");
        exit(1);
    }
    if (close(fd) < 0) {
        printf("Error 2!\n");
        exit(1);
    }

    FILE *file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = (char *) malloc(fsize * sizeof(char));
    fread(content, 1, fsize, file);
    fclose(file);

    if (remove(filename) < 0) {
        printf("Error 1!\n");
        exit(1);
    }

    if (content) {
        puts(content);
        free(content);
    }
    return 0;
}
