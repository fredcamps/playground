# include <stdio.h>
# include <stdlib.h>

typedef enum color_t {
    RED, BLACK
} color;

typedef enum boolean_t {
    True,
    False
} boolean;

typedef enum direction_t {
    RIGHT,
    LEFT
} direction;

typedef struct node {
    int key;
    struct node *parent;
    struct node *left;
    struct node *right;
    color color;
} Node;

typedef struct red_black_tree {
    struct node *root;
    struct node *(*insert)(int key);
    struct node *(*find)(int key);
    int (*purge)(int key);
    void (*display)();
    void (*destroy)();
} RedBlackTree;

static RedBlackTree *tree;

static int is_red(Node *n)
{
    return (n != NULL && n->color == RED);
}

static int has_parent(Node *n)
{
    return (n != NULL && n->parent != NULL);
}

static int is_null_node(Node *n)
{
    return (n == NULL);
}

static Node *minimum(Node *n)
{
    Node *current = n;
    if (is_null_node(current)) {
        return current;
    }
    while (!is_null_node(current->left)) {
        current = current->left;
    }
    return current;
}

static Node *predecessor(RedBlackTree *t, int key)
{
    Node *walk_node = t->root;
    Node *tmp_node = NULL;

    while (1) {
        if (is_null_node(walk_node)) {
            break;
        }
        tmp_node = walk_node;
        walk_node = (key < walk_node->key) ?
            walk_node->left :
            walk_node->right;
    }

    return tmp_node;
}

static void left_rotate(RedBlackTree *t, Node *n)
{
    Node *right_child = n->right;
    Node *parent = n->parent;

    n->right = (right_child == NULL) ? NULL : right_child->left;
    if (!is_null_node(right_child->left)) {
        right_child->left->parent = n;
    }
    right_child->parent = parent;
    if (is_null_node(parent)) {
        t->root = right_child;
    } else if (n == parent->left) {
        parent->left = right_child;
    } else {
        parent->right = right_child;
    }

    right_child->left = n;
    n->parent = right_child;
}

static void right_rotate(RedBlackTree *t, Node *n)
{
    Node *left_child = n->left;
    Node *parent = n->parent;

    n->left = (left_child == NULL) ? NULL : left_child->right;
    if (!is_null_node(left_child->right)) {
        left_child->right->parent = n;
    }
    left_child->parent = parent;
    if (is_null_node(parent)) {
        t->root = left_child;
    } else if (parent->left == n) {
        parent->left = left_child;
    } else {
        parent->right = left_child;
    }

    left_child->right = n;
    n->parent = left_child;
}

static Node *create_node(int key)
{
    Node *n = (Node *) malloc(sizeof(Node));
    n->parent = NULL;
    n->color = RED;
    n->key = key;
    n->right = NULL;
    n->left = NULL;
    return n;
}

static void transplant(RedBlackTree *t, Node *prev, Node *current)
{
    if (!has_parent(prev)) {
        t->root = current;
    } else if (prev == prev->parent->left) {
        prev->parent->left = current;
    } else {
        prev->parent->right = current;
    }
    if(!is_null_node(current)) {
        current->parent = prev->parent;
    }
}

static Node *search(RedBlackTree *t, int key)
{
    Node *n = t->root;
    if (is_null_node(n)) {
        return n;
    }
    while (!is_null_node(n) && n->key != key) {
        if (n->key > key) {
            n = is_null_node(n->left) ? NULL : n->left;
        } else {
            n = is_null_node(n->right) ? NULL: n->right;
        }
    }

    return n;
}

static void deletion_fixup(RedBlackTree *t,
                           Node *n,
                           Node *node_parent,
                           direction _direction)
{
    while (n != t->root && !is_red(n)) {
        Node *uncle = NULL;
        Node *parent = (n == NULL) ? node_parent : n->parent;

        if (n == parent->left || _direction == LEFT) {
			uncle  = parent->right;
			if (is_red(uncle)) {
				uncle->color = BLACK;
				parent->color = RED;
				left_rotate(tree, parent);
				uncle = parent->right;
			}
			if (!is_red(uncle->left) && !is_red(uncle->right)) {
				uncle->color = RED;
				n = (n == NULL) ? node_parent : n->parent;
			} else if (!is_red(uncle->right)) {
				uncle->color = RED;
				uncle->left->color = BLACK;
				right_rotate(t, uncle);
				uncle = parent->right;
			} else {
				parent->color = BLACK;
				uncle->color = RED;
				uncle->right->color = BLACK;
				left_rotate(t, parent);
				n = t->root;
            }
        } else {
            uncle = parent->left;
            if (is_red(uncle)) {
				uncle->color = BLACK;
				parent->color = RED;
				right_rotate(t, parent);
				uncle = parent->left;
			}
			if (!is_red(uncle->right) && !is_red(uncle->left)) {
				uncle->color = RED;
				n = (n == NULL) ? node_parent : n->parent;
			} else if (!is_red(uncle->left)) {
				uncle->color = RED;
				uncle->right->color = BLACK;
				left_rotate(t, uncle);
				uncle = parent->left;
			} else {
				parent->color = BLACK;
				uncle->color = RED;
				uncle->left->color = BLACK;
				right_rotate(t, parent);
				n = t->root;
            }
        }
    }
    if (!is_null_node(n)) {
        n->color = BLACK;
    }
}


static int deletion(RedBlackTree *t, Node *n)
{
    Node *walk_node = n;
    Node *need_fixup_node = NULL;
    Node *need_fixup_node_parent = NULL;
    color tmp_color = walk_node->color;
    direction _direction = LEFT;
    int deleted_key = 0;

    if (is_null_node(n->left)) {
        need_fixup_node = n->right;
        need_fixup_node_parent =
            is_null_node(need_fixup_node) ? n->parent : n;
        _direction = RIGHT;
        transplant(t, n, need_fixup_node);
        if (is_null_node(need_fixup_node)) {
            need_fixup_node_parent = n->parent;
        }
    } else if (is_null_node(n->right)) {
        need_fixup_node = n->left;
        need_fixup_node_parent = n;
        _direction = LEFT;
        transplant(t, n, need_fixup_node_parent);
    } else {
        walk_node = minimum(n->right);
        tmp_color = walk_node->color;
        need_fixup_node = walk_node->right;
        need_fixup_node_parent = walk_node;
        _direction = RIGHT;
        if (walk_node->parent != n) {
            Node *tmp_node = walk_node->right;
            transplant(t, walk_node, tmp_node);
            if (is_null_node(need_fixup_node)) {
                need_fixup_node_parent = walk_node->parent;
            }
            walk_node->right = n->right;
            walk_node->right->parent = walk_node;
        }
        transplant(t, n, walk_node);
        walk_node->left = n->left;
        walk_node->left->parent = walk_node;
        walk_node->color = n->color;
    }

    if (tmp_color == BLACK) {
        deletion_fixup(t,
                       need_fixup_node,
                       need_fixup_node_parent,
                       _direction);
    }
    deleted_key = n->key;
    free(n);
    n = NULL;
    return deleted_key;
}

static void insertion_fixup(RedBlackTree *t, Node *n)
{
    Node *parent = NULL;
    Node *uncle = NULL;
    Node *tmp_node = NULL;

    while (is_red(n)) {
        parent = n->parent;
        if (!is_red(parent)) {
            break;
        }
        Node *grand_parent = parent->parent;
        if (parent == grand_parent->left) {
            uncle = grand_parent->right;
            if (is_red(uncle)) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand_parent->color = RED;
                n = grand_parent;
            } else {
                if (n == parent->right) {
                    left_rotate(t, parent);
                    tmp_node = n;
                    n = parent;
                    parent = tmp_node;
                } else {
                    parent->color = BLACK;
                    grand_parent->color = RED;
                    right_rotate(t, grand_parent);
                }
            }
        } else {
            uncle = grand_parent->left;
            if (is_red(uncle)) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand_parent->color = RED;
                n = grand_parent;
            } else {
                if (n == parent->left) {
                    right_rotate(t, parent);
                    tmp_node = n;
                    n = parent;
                    parent = tmp_node;
                } else {
                    parent->color = BLACK;
                    grand_parent->color = RED;
                    left_rotate(t, grand_parent);
                }
            }
        }
    }
    t->root->color = BLACK;
}

static Node *insertion(RedBlackTree *t, Node *n)
{
    Node *tmp_node = predecessor(t, n->key);

    if(is_null_node(tmp_node)) {
        t->root = n;
    } else if (n->key > tmp_node->key) {
        tmp_node->right = n;
    } else {
        tmp_node->left = n;
    }
    n->parent = tmp_node;

    insertion_fixup(t, n);
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
    return search(tree, key);
}

Node *insert(int key)
{
    Node *n = NULL;
    n = create_node(key);
    return insertion(tree, n);
}

int purge(int key)
{
    Node *to_delete = search(tree, key);
    return deletion(tree, to_delete);
}

void display()
{
    inorder_helper(tree->root);
}

void destroy()
{
    free(tree->root);
    free(tree);
}

RedBlackTree *make_redblack_tree()
{
    RedBlackTree *t = (RedBlackTree *) malloc(sizeof(RedBlackTree));
    t->insert = insert;
    t->find = find;
    t->purge = purge;
    t->display = display;
    t->destroy = destroy;
    return t;
}

int main(int argc, char *argv[])
{
    tree = make_redblack_tree();
    tree->insert(7);
    tree->insert(6);
    tree->insert(5);
    tree->insert(4);
    tree->insert(3);
    tree->insert(2);
    tree->insert(1);
    printf("\nPrinting In Order Traversal (Before Delete): ");
    tree->display();

    tree->purge(7);
    tree->purge(2);
    tree->purge(1);

    printf("\n Printing In Order Traversal (After Delete): ");
    tree->display();
    tree->destroy();
    return 0;
}
