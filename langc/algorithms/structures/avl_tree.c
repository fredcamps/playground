/**
 * @author Fred Campos <fred.tecnologia@gmail.com>
 *
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int key;
    int height;
    struct node *left;
    struct node *right;
    struct node *(*insert)(int key);
    struct node *(*search)(int key);
    struct node *(*purge)(int key);
    void (*display)();
} Node;

typedef Node AVLTree;

static Node *root;

static Node *search(int key);

static int max(int l, int r)
{
    return (l > r) ? l : r;
}

static int height(Node *n)
{
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

static int get_balance_factor(Node *n)
{
    if (n == NULL) {
        return 0;
    }
    return height(n->left) - height(n->right);
}

static Node *update_heights(Node *n)
{
    n->height = max(height(n->left), height(n->right))+1;
    return n;
}

static Node *left_rotate(Node *x)
{
    Node *y = x->right;
    Node *z = y->left;

    // Perform rotation
    y->left = x;
    x->right = z;

    //  Update heights
    x = update_heights(x);
    y = update_heights(y);

    // Return new subtree root
    return y;
}

static Node *right_rotate(Node *y)
{
    Node *x = y->left;
    Node *z = x->right;

    // Perform rotation
    x->right = y;
    y->left = z;

    // Update heights
    y = update_heights(y);
    x = update_heights(x);

    // Return new subtree root
    return x;
}

static Node *create_node(int key)
{
    Node *n = (Node *) malloc(sizeof(Node));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

static Node *get_smallest_subtree_node(Node *n)
{
    Node *current = n;
    while(current->left != NULL) {
        current = current->left;
    }
    return current;
}


static Node *insertion(int key, Node *n)
{
    if (n == NULL) {
        return create_node(key);
    }

    // find the position to insert node
    if (key < n->key) {
        n->left = insertion(key, n->left);
    } else if (key > n->key) {
        n->right = insertion(key, n->right);
    } else {
        return n;
    }

    // update heights
    n->height = 1 + max(height(n->left),
                        height(n->right));

    // check whether this node became unbalanced)
    int balance = get_balance_factor(n);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < n->left->key) {
        return right_rotate(n);
    }

    // Right Right Case
    if (balance < -1 && key > n->right->key) {
        return left_rotate(n);
    }

    // Left Right Case
    if (balance > 1 && key > n->left->key) {
        n->left =  left_rotate(n->left);
        return right_rotate(n);
    }

    // Right Left Case
    if (balance < -1 && key < n->right->key) {
        n->right = right_rotate(n->right);
        return left_rotate(n);
    }

    return n;
}


static Node *purge_item(int key, Node *n)
{
    if (n == NULL) {
        return n;
    }

    // find item to delete
    if (key < n->key) {
        n->left = purge_item(key, n->left);
    } else if(key > n->key) {
        n->right = purge_item(key, n->right);
    } else /* if item has found */{
        // node with only one child or no child
        if ((n->left == NULL) || (n->right == NULL)) {
            Node *temp = n->left ? n->left : n->right;
            // No child case
            if (temp == NULL) {
                temp = n;
                n = NULL;
            } else  /* One child case */ {
                *n = *temp; // Copy the contents of
                            // the non-empty child
            }
            free(temp);
        } else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = get_smallest_subtree_node(n->right);

            // Copy the inorder successor's data to this node
            n->key = temp->key;

            // Delete the inorder successor
            n->right = purge_item(temp->key, n->right);
        }
    }

    // If the tree had only one node then return
    if (n == NULL) {
        return n;
    }

    // update heights
    n->height = 1 + max(height(n->left),
                        height(n->right));

    // check whether this node became unbalanced)
    int balance = get_balance_factor(n);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && get_balance_factor(n->left) >= 0) {
        return right_rotate(n);
    }

    // Left Right Case
    if (balance > 1 && get_balance_factor(n->left) < 0) {
        n->left =  left_rotate(n->left);
        return right_rotate(n);
    }

    // Right Right Case
    if (balance < -1 && get_balance_factor(n->right) <= 0) {
        return left_rotate(n);
    }

    // Right Left Case
    if (balance < -1 && get_balance_factor(n->right) > 0) {
        n->right = right_rotate(n->right);
        return left_rotate(n);
    }

    return n;
}

Node *insert(int key)
{
    root = insertion(key, root);
    return root;
}

Node *search(int key)
{
    Node *n = root;

    if (n == NULL) {
        return n;
    }

    while(n->key != key) {
        if (n->key > key) {
            n = n->left;
        } else {
            n = n->right;
        }
        if (n == NULL) {
            return n;
        }
    }
    return n;
}

Node *purge(int key)
{
    root = purge_item(key, root);
    return root;
}


static void pre_order(Node *r)
{
    if (r != NULL) {
        printf("%d ", r->key);
        pre_order(r->left);
        pre_order(r->right);
    }
}

static void in_order(Node *r)
{
    if (r != NULL) {
        in_order(r->left);
        printf("%d ", r->key);
        in_order(r->right);
    }
}

static void post_order(Node *r)
{
    if (r != NULL) {
        post_order(r->left);
        post_order(r->right);
        printf("%d ", r->key);
    }
}

void display()
{
    printf(" Pre Order Traversal: ");
    pre_order(root);
    printf(" In Order Traversal: ");
    in_order(root);
    printf(" Post Order Traversal; ");
    post_order(root);
}

AVLTree *make_avl_tree()
{
    AVLTree *t = (AVLTree *) malloc(sizeof(AVLTree));
    t->insert = insert;
    t->purge = purge;
    t->search = search;
    t->display = display;
    return t;
}

int main(int argc, char *argv[])
{
    AVLTree *tree = make_avl_tree();
    tree->insert(9);
    tree->insert(5);
    tree->insert(10);
    tree->insert(0);
    tree->insert(6);
    tree->insert(11);
    tree->insert(-1);
    tree->insert(1);
    tree->insert(2);

    printf("\n > Before item deletion: \n");
    tree->display();
    tree->purge(10);
    printf("\n > After item deletion: \n");
    tree->display();

    free(tree);
    return 0;
}
