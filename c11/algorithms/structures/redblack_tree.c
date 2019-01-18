# include <stdio.h>
# include <stdlib.h>

typedef enum color_t {
    red, black
} color;

typedef struct node {
    int key;
    struct node *parent;
    struct node *left;
    struct node *right;
    color color;
    struct node *(*insert)(int data);
    struct search *(*search)(int data);
    struct delete *(*delete)(int data);
} Node;

Node *root;

typedef Node RedBlackTree;

static Node *get_smallest_subtree_node(Node *n) {
    Node *current = n;
    while(current->left != NULL) {
        current = current->left;
    }
    return current;
}

static Node *left_rotate(Node *r, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        r = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    y->parent = y;

    return y;
}

static Node *right_rotate(Node *r, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = x;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        r = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    x->parent = y;

    return x;
}

static Node *create_node(int key)
{
    Node *n = (Node *) malloc(sizeof(Node));
    n->color = black;
    n->key = key;
    n->right = NULL;
    n->left = NULL;
}

static Node *transplant(Node * r, Node *x, Node *y)
{
    if (x->parent == NULL) {
        r = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->parent = x->parent;

    return r;
}

static Node *deletion_fixup(Node *r, Node *x)
{
    Node *w = NULL;
    while ((x != r) && (x->color == black)) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == red) {
                w->color = black;
                x->parent->color = red;
                left_rotate(r, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == black &&
                w->right->color == black) {
                w->color = red;
                x = x->parent;
            } else if (black == w->right->color) {
                w->left->color = black;
                w->color = red;
                right_rotate(r, w);
                w = x->parent->right;
            } else {
                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                left_rotate(r, x->parent);
                x = r;
            }
        } else {
            w = x->parent->left;
            if (w->color == red) {
                w->color = black;
                x->parent->color = red;
                right_rotate(r, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == black &&
                w->left->color == black) {
                w->color = red;
                x = x->parent;
            } else if (black == w->left->color) {
                w->right->color = black;
                w->color = red;
                left_rotate(r, w);
                w = x->parent->left;
            } else {
                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                right_rotate(r, x->parent);
                x = r;
            }
        }
    }
    x->color = black;
    return x;
}

static Node *deletion(Node *r, Node *z)
{
    Node *x = NULL;
    Node *y = z;
    color y_original_color = y->color;
    if (z->left == NULL) {
        x = z->right;
        transplant(r, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(r, z, z->left);
    } else {
        y = get_smallest_subtree_node(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(r, y, y->right);
            y->right = z->right;
        }
        transplant(r, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == black) {
        deletion_fixup(r, x);
    }
}

static Node *insertion_fixup(Node *r, Node *z)
{
    Node *y = NULL;
    while (z->parent->color == red) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == red) {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            } else if (z == z->parent->right) {
                z = z->parent;
                left_rotate(r, z);
            } else {
                z->parent->color = black;
                z->parent->parent->color = red;
                right_rotate(r, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (z->color == red) {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            } else if (z == z->parent->left) {
                z = z->parent;
                right_rotate(r, z);
            } else {
                z->parent->color = black;
                z->parent->parent->color = red;
                left_rotate(r, z->parent->parent);
            }

        }
    }
    r->color = black;
    return r;
}

static Node *insertion(Node *r, Node *z)
{
    Node *y = NULL;
    Node *x = r;
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NULL) {
        r = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = NULL;
    z->right = NULL;
    z->color = red;

    return insertion_fixup(r, z);
}

Node *insert(int key)
{
}

Node *purge(int key)
{
}


int main(int argc, char *argv[])
{

    return 0;
}
