# include <stdio.h>
# include <stdlib.h>

/**
 * WIP: Implementing hash table
 */
const int SIZE = 20;

typedef struct node {
    int key;
    int value;
} Node;


typedef struct hash_table {
    Node *nodes;
    int size;
    void (*insert)(int key, int value);
    void (*delete)(int key);
    void (*destroy)();
    Node *(*get)(int key);
    Node *(*search)(int value);
} HashTable;

HashTable *hash_table;

int hash_code(int key) {
    return -1;
}

void hash_table_insert(int key, int value) {

}

Node *hash_table_search(int value) {
    Node *node;
    return node;
}

Node *hash_table_get(int key) {
    Node *node;
    return node;
}

void hash_table_delete(int key) {

}

void hash_table_destroy() {

}

HashTable *make_hash_table () {
    hash_table = (HashTable *) malloc(sizeof(HashTable));
    hash_table->size = SIZE;
    hash_table->insert = hash_table_insert;
    hash_table->search = hash_table_search;
    hash_table->get = hash_table_get;
    hash_table->delete = hash_table_delete;
    hash_table->destroy = hash_table_destroy;
    return hash_table;
}


int main(int argc, char *argv[])
{
    HashTable *dict = make_hash_table();
    dict->insert(1, 20);
    dict->insert(2, 30);
    dict->insert(4, 40);
    return 0;
}
