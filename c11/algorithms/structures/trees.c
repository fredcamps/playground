# include <stdio.h>
# include <stdlib.h>


typedef enum color_type {
    Red, Black
} ColorType;


typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;


typedef struct red_black_node {
    int value;
    struct node *left;
    struct node *right;
    ColorType color;
} RedBlackNode;


int main(int argc, char *argv[])
{

    return 0;
}
