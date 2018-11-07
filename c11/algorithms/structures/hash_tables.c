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
    Node *nodes[SIZE];
    void (*insert)(int key, int value);
    void (*delete)(int key);
    void (*destroy)();
    Node *(*get)(int key);
} HashTable;

HashTable *hash_table;

int hash_code(int key) {
    return key % SIZE;
}

void hash_table_insert(int key, int value) {
    int hash_index = hash_code(key);
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->value = value;

    while (hash_table->nodes[hash_index] != NULL &&
           hash_table->nodes[hash_index]->key != -1) {
        ++hash_index;
        hash_index %= SIZE;
    }
    hash_table->nodes[hash_index] = node;
}

Node *hash_table_get(int key) {
    int hash_index = hash_code(key);


    while (hash_table->nodes[hash_index] != NULL) {
        if (hash_table->nodes[hash_index]->key == key) {
            return hash_table->nodes[hash_index];
        }
    }

    return NULL;
}

void hash_table_delete(int key) {

}

void hash_table_destroy() {

}

HashTable *make_hash_table () {
    hash_table = (HashTable *) malloc(sizeof(HashTable));
    hash_table->insert = hash_table_insert;
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
