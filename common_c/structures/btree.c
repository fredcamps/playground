#include <stdio.h>
#include <stdlib.h>

#define MAX 4
#define MIN 2

typedef struct node_t {
    int values[MAX + 1];
    int count;
    struct node_t *links[MAX + 1];
} Node;

typedef struct btree_t {
    Node *root;
    void (*insert)(int value);
    void (*purge)(int value);
    Node *(*search)(int value);
    void (*traversal)();
} BTree;

BTree *tree;

/* creating new node */
static Node *create_node(int value, Node *child)
{
    Node *new_node;
    new_node = (Node *) malloc(sizeof(Node));
    new_node->values[1] = value;
    new_node->count = 1;
    new_node->links[0] = tree->root;
    new_node->links[1] = child;
    return new_node;
}

/* Places the value in appropriate position */
static void add_value_to_node(int val, int pos, Node *node, Node *child)
{
    int i = node->count;
    while (i > pos) {
        node->values[i + 1] = node->values[i];
        node->links[i + 1] = node->links[i];
        i--;
    }
    node->values[i + 1] = val;
    node->links[i + 1] = child;
    node->count++;
}

/* split the node */
static void split_node (int val, int *pval, int pos, Node *node,
                 Node *child, Node **new_node)
{
    int median, i;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *new_node = (Node *)malloc(sizeof(Node));
    i = median + 1;
    while (i <= MAX) {
        (*new_node)->values[i - median] = node->values[i];
        (*new_node)->links[i - median] = node->links[i];
        i++;
    }
    node->count = median;
    (*new_node)->count = MAX - median;

    if (pos <= MIN) {
        add_value_to_node(val, pos, node, child);
    } else {
        add_value_to_node(val, pos - median, *new_node, child);
    }
    *pval = node->values[node->count];
    (*new_node)->links[0] = node->links[node->count];
    node->count--;
}

/* sets the value val in the node */
static int set_value_in_node(int val, int *pval,
                             Node *node, Node **child)
{
    int pos;
    if (!node) {
        *pval = val;
        *child = NULL;
        return 1;
    }

    if (val < node->values[1]) {
        pos = 0;
    } else {
        for (pos = node->count;
             (val < node->values[pos] && pos > 1); pos--);
        if (val == node->values[pos]) {
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (set_value_in_node(val, pval, node->links[pos], child)) {
        if (node->count < MAX) {
            add_value_to_node(*pval, pos, node, *child);
        } else {
            split_node(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

/* insert val in B-Tree */
void insertion(int val)
{
    Node *child;
    int has_no_root, i;
    has_no_root = set_value_in_node(val, &i, tree->root, &child);
    if (has_no_root) {
        tree->root = create_node(i, child);
    }
}

/* delete val from B-tree */
static void deletion(int val, Node *node)
{
    /* Not implemented yet */
}

void purge(int val)
{
    return deletion(val, tree->root);
}

/* search val in B-Tree */
Node *searching(int val, int *pos, Node *node)
{
    if (!node) {
        return NULL;
    }
    if (val < node->values[1]) {
        *pos = 0;
    } else {
        for (*pos = node->count;
             (val < node->values[*pos] && *pos > 1); (*pos)--);
        if (val == node->values[*pos]) {
            return node;
        }
    }
    return searching(val, pos, node->links[*pos]);
}

Node *search(int val)
{
    int pos;
    return searching(val, &pos, tree->root);
}

/* B-Tree Traversal */
void do_traversal(Node *node)
{
    int i;
    if (node != NULL) {
        for (i = 0; i < node->count; i++) {
            do_traversal(node->links[i]);
            printf("%d ", node->values[i + 1]);
        }
        do_traversal(node->links[i]);
    }
}

void traversal()
{
    do_traversal(tree->root);
}


BTree *btree()
{
    BTree *bt = (BTree *) malloc(sizeof(BTree));
    bt->insert = insertion;
    bt->purge = purge;
    bt->search = search;
    bt->traversal = traversal;
    return bt;
}


int main()
{
    tree = btree();
    tree->insert(6);
    tree->insert(7);
    tree->insert(5);
    tree->insert(4);
    tree->insert(3);
    tree->insert(2);
    tree->insert(1);

    printf("\nB-Tree Traversal before deletion(s): \n");
    tree->traversal();
}
