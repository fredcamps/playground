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
    struct node *(*insert)(int key);
    struct node *(*find)(int key);
    struct node *(*purge)(int key);
    void (*display)();
} Node;

static Node *root;

typedef Node RedBlackTree;

static void swap_colors(color *color1, color *color2)
{
    color *temp = color1;
    *color1 = *color2;
    *color2 = *temp;
}

static Node *get_smallest_subtree_node(Node *n) {
    Node *current = n;

    if (current == NULL) {
        return current;
    }

    while(current->left != NULL) {
        current = current->left;
    }
    return current;
}

static Node *left_rotate(Node *r, Node *n)
{
    Node *right = n->right;
    n->right = right->left;
    if (n->right != NULL) {
        n->right->parent = n;
    }
    right->parent = n->parent;

    if (n->parent == NULL) {
        r = right;
    } else if (n == n->parent->left) {
        n->parent->left = right;
    } else {
        n->parent->right = right;
    }

    right->left = n;
    n->parent = right;

    return r;
}

static Node *right_rotate(Node *r, Node *n)
{
    Node *left = n->left;
    n->left = left->right;
    if (n->left != NULL) {
        n->left->parent = n;
    }
    left->parent = n->parent;

    if (n->parent == NULL) {
        r = left;
    } else if (n == n->parent->left) {
        n->parent->left = left;
    } else {
        n->parent->right = left;
    }

    left->right = n;
    n->parent = left;

    return r;
}

static Node *create_node(int key)
{
    Node *n = (Node *) malloc(sizeof(Node));
    n->color = black;
    n->key = key;
    n->right = NULL;
    n->left = NULL;
    return n;
}

static Node *transplant(Node *r, Node *x, Node *y)
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

static Node *insertion_fixup(Node *r, Node *n)
{
    Node *parent_node = NULL;
    Node *grand_parent_node = NULL;

    while ((n != r) &&
           (n->color != black) &&
           (n->parent->color == red)) {

        parent_node = n->parent;
        grand_parent_node = n->parent->parent;

        if (parent_node == grand_parent_node->left) {

            if (grand_parent_node->right != NULL &&
                grand_parent_node->right->color == red) {
                grand_parent_node->color = red;
                parent_node->color = black;
                grand_parent_node->right->color = black;
                n = grand_parent_node;
            } else {
                if (n == parent_node->right) {
                    left_rotate(r, parent_node);
                    n = parent_node;
                    parent_node = n->parent;
                }

                right_rotate(r, grand_parent_node);
                swap_colors(&parent_node->color,
                            &grand_parent_node->color);
                n = parent_node;
            }
        } else {

            if ((grand_parent_node->left != NULL) &&
                (grand_parent_node->left->color = red)) {
                grand_parent_node->color = red;
                parent_node->color = black;
                grand_parent_node->left->color = black;
                n = grand_parent_node;
            } else {
                if (n == parent_node->left) {
                    right_rotate(r, parent_node);
                    n = parent_node;
                    parent_node = n->parent;
                }

                left_rotate(r, grand_parent_node);
                swap_colors(&parent_node->color,
                            &grand_parent_node->color);
            }
        }
    }
    return r;
}

static Node *insertion(Node *r, int key)
{
    Node *item = NULL;
    if (r == NULL) {
        r = create_node(key);
        return r;
    }

    if (key < r->key) {
        r->left = insertion(r->left, key);
        r->left->parent = r;
        item = r->left;
    } else if (key > r->key) {
        r->right = insertion(r->right, key);
        r->right->parent = r;
        item = r->right;
    }

    return insertion_fixup(r, item);
}

static Node *search(Node *r, int key)
{
    Node *n = r;
    while (n->key != key) {
        if (n == NULL) {
            return n;
        }
        if (n->key > key) {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    return n;
}


static void inorder_helper(Node *r)
{
    if (r == NULL) {
        return;
    }
    inorder_helper(r->left);
    printf("%d ", r->key);
    inorder_helper(r->right);
}

Node *find(int key)
{
    return search(root, key);
}

Node *insert(int key)
{
    root = insertion(root, key);
    return root;
}

Node *purge(int key)
{
    Node *to_delete = find(key);
    /* Not implement deletion yet */
    return root;
}

void display()
{
    inorder_helper(root);
}


RedBlackTree *make_redblack_tree()
{
    RedBlackTree *t = (RedBlackTree *)  malloc(sizeof(RedBlackTree));
    t->insert = insert;
    t->find = find;
    t->purge = purge;
    t->display = display;
    return t;
}


int main(int argc, char *argv[])
{
    RedBlackTree *tree = make_redblack_tree();
    tree->insert(7);
    tree->insert(6);
    tree->insert(5);
    tree->insert(4);
    tree->insert(3);
    tree->insert(2);
    tree->insert(1);
    printf("\nPrinting In Order Traversal (Before Delete): ");
    tree->display();

    /* tree->purge(7); */
    /* tree->purge(2); */
    /* tree->purge(1); */

    /* printf("\n Printing In Order Traversal (After Delete): "); */
    /* tree->display(); */

    free(tree);
    return 0;

}
