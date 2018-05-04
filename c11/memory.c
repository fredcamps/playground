#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[]) {

    char *full_name;
    char first_name[20];
    char last_name[20];

    char *token;

    char first_char;
    char second_char;
    char third_char;

    printf("\nEnter your first name: ");
    full_name = malloc(20 * sizeof(char));
    fgets(first_name, sizeof(first_name), stdin);
    strtok(first_name, "\n");
    strcpy(full_name, first_name);

    printf("\nEnter your second name: ");
    full_name = realloc(full_name, 40 * sizeof(char));
    fgets(last_name, sizeof(first_name), stdin);
    strtok(last_name, "\n");
    strcat(full_name, " ");
    strcat(full_name, last_name);

    printf("\nFull name: %s", full_name);

    first_char = *(first_name + 0);
    second_char = *(first_name + 1);
    third_char = *(full_name + 2);

    printf("\nfirst char from first_name: %c", first_char);
    printf("\nsecond char from first_name: %c", second_char);
    printf("\nthird char from full_name: %c", third_char);

    token = strtok(full_name, " ");
    printf("\nprinting tokens...");
    while (token != NULL)
    {
        printf("\n%s", token);
        token = strtok(NULL, " ");
    }

    printf("\n");
    free(full_name);

    printf("\npointer manipulation");

    int i = 10;
    int *p;
    int **pp;
    p = &i;
    pp = &p;
    printf("\nvalue of i: %d", i);
    printf("\nvalue of p: %d", *p);
    printf("\nincrement of p: %d", ++(*p));
    printf("\nnew value of i: %d", i);
    printf("\nincrement of pp: %d", ++(**pp));
    printf("\nnewest value of i: %d", i);
    printf("\n");

    return 0;
}
