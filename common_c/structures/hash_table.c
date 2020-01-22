#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int SIZE = 20;

typedef struct node_t {
    int key;
    int value;
} Node;

typedef struct hash_table_t {
    Node *nodes[SIZE];
    void (*insert)(int key, int value);
    void (*delete)(int key);
    void (*destroy)();
    Node *(*get)(int key);
} HashTable;

HashTable *hash_table;

int hash_code(int key)
{
    return key % SIZE;
}

void hash_table_insert(int key, int value)
{
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

Node *hash_table_get(int key)
{
    int hash_index = hash_code(key);
    while (hash_table->nodes[hash_index] != NULL) {
        if (hash_table->nodes[hash_index]->key == key) {
            return hash_table->nodes[hash_index];
        }
    }
    return NULL;
}

void hash_table_delete(int key)
{
    //get the hash
    int hash_index = hash_code(key);

    Node *dummy_item = (Node*) malloc(sizeof(Node));
    dummy_item->value = -1;
    dummy_item->key = -1;

    // move in array until an empty
    while (hash_table->nodes[hash_index] !=NULL) {
        if(hash_table->nodes[hash_index]->key == key) {
            // Node* temp = hash_table->nodes[hash_index];
            //assign a dummy item at deleted position
            hash_table->nodes[hash_index] = dummy_item;
            return;
        }
        //go to next cell
        ++hash_index;

        //wrap around the table
        hash_index %= SIZE;
    }
}

void hash_table_destroy()
{
    free(hash_table);
}

HashTable *make_hash_table ()
{
    hash_table = (HashTable *) malloc(sizeof(HashTable));
    hash_table->insert = hash_table_insert;
    hash_table->get = hash_table_get;
    hash_table->delete = hash_table_delete;
    hash_table->destroy = hash_table_destroy;
    return hash_table;
}

int main(int argc, char *argv[])
{
    HashTable *h = make_hash_table();
    h->insert(1, 20);
    h->insert(2, 30);
    h->insert(4, 40);
    h->delete(4);
    Node *temp = h->get(2);
    assert(temp->key == 2);
    printf("%d", temp->key);
    h->destroy();
    return 0;
}
