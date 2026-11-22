#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define SIZE 20

typedef struct node_t {
    int key;
    int value;
} Node;

typedef struct hash_table_t {
    Node *nodes[SIZE];
    bool (*insert)(int key, int value);
    void (*delete)(int key);
    void (*destroy)(void);
    Node *(*get)(int key);
} HashTable;

static HashTable *hash_table = NULL;
static Node DUMMY_NODE = { .key = -1, .value = -1 };

/*
 * Open Addressing with Linear Probing hashing collision avoidance strategy
 */
int hash_code(int key)
{
    int idx = key % SIZE;
    return idx < 0 ? idx + SIZE : idx;
}


bool hash_table_insert(int key, int value)
{
		assert(key != -1 && "Key -1 is reserved for tombstone sentinel");

    int hash_index = hash_code(key);
    int first_tombstone = -1;

    for (int i = 0; i < SIZE; i++) {
        Node *curr = hash_table->nodes[hash_index];

        if (curr == NULL) {
            int target = (first_tombstone != -1) ? first_tombstone : hash_index;
            Node *node = malloc(sizeof(Node));
            if (!node) return false;
            node->key = key;
            node->value = value;
            hash_table->nodes[target] = node;
            return true;
        }

       if (curr == &DUMMY_NODE) {
           if (first_tombstone == -1) {
               first_tombstone = hash_index;
           }
       } else if (curr->key == key) {
           curr->value = value;
           return true;
       }

       hash_index = (hash_index + 1) % SIZE;
    }

		// If the table had no NULL slots left, reuse the first tombstone we passed
    if (first_tombstone != -1) {
        Node *node = malloc(sizeof(Node));
        if (!node) return false;
        node->key = key;
        node->value = value;
        hash_table->nodes[first_tombstone] = node;
        return true;
    }

    return false;
}

Node *hash_table_get(int key)
{
		if (key == -1) return NULL;
    int hash_index = hash_code(key);
		for (int i = 0; i < SIZE; i++) {
				Node *curr = hash_table->nodes[hash_index];
				if (curr == NULL) {
						return NULL;
				}
				if (curr != &DUMMY_NODE && curr->key == key) {
						return curr;
				}
				hash_index = (hash_index + 1) % SIZE;
    }
    return NULL;
}

void hash_table_delete(int key)
{
		// get the hash
		if (key == -1) return;
    int hash_index = hash_code(key);

		for (int i = 0; i < SIZE; i++) {
        Node *curr = hash_table->nodes[hash_index];
        if (curr == NULL) {
            return;
        }
        if (curr != &DUMMY_NODE && curr->key == key) {
            free(curr);
            hash_table->nodes[hash_index] = &DUMMY_NODE;
						return;
        }
        hash_index = (hash_index + 1) % SIZE;
    }
}

void hash_table_destroy(void)
{
		if (!hash_table)
				return;

		for (int i = 0; i < SIZE; i++) {
        Node *curr = hash_table->nodes[i];
        if (curr != NULL && curr != &DUMMY_NODE) {
            free(curr);
        }
    }

    free(hash_table);
}

HashTable *make_hash_table (void)
{
		hash_table = calloc(1, sizeof(HashTable));
    if (!hash_table) return NULL;
    hash_table->insert = hash_table_insert;
    hash_table->get = hash_table_get;
    hash_table->delete = hash_table_delete;
    hash_table->destroy = hash_table_destroy;
    return hash_table;
}

void test_basic_insert_and_get(void)
{
    HashTable *h = make_hash_table();
    assert(h != NULL);

    assert(h->insert(1, 20) == true);
    assert(h->insert(2, 30) == true);

    Node *n1 = h->get(1);
    Node *n2 = h->get(2);
    assert(n1 != NULL && n1->key == 1 && n1->value == 20);
    assert(n2 != NULL && n2->key == 2 && n2->value == 30);
    assert(h->get(999) == NULL); // Non-existent key

    h->destroy();
    printf("[PASS] test_basic_insert_and_get\n");
}

void test_update_existing_key(void)
{
    HashTable *h = make_hash_table();

    assert(h->insert(5, 100) == true);
    assert(h->insert(5, 250) == true); // Should overwrite in-place, not duplicate

    Node *n = h->get(5);
    assert(n != NULL && n->value == 250);

    // Deleting once should completely remove key 5 (proves no duplicate existed)
    h->delete(5);
    assert(h->get(5) == NULL);

    h->destroy();
    printf("[PASS] test_update_existing_key\n");
}

void test_collisions_and_wrap_around(void)
{
    HashTable *h = make_hash_table();

    // Keys 19, 39, 59 all hash to index 19 (SIZE - 1), forcing wrap-around to 0 and 1
    assert(h->insert(19, 190) == true);
    assert(h->insert(39, 390) == true);
    assert(h->insert(59, 590) == true);

    assert(h->get(19)->value == 190);
    assert(h->get(39)->value == 390);
    assert(h->get(59)->value == 590);

    h->destroy();
    printf("[PASS] test_collisions_and_wrap_around\n");
}

void test_tombstone_chain_and_reuse(void)
{
    HashTable *h = make_hash_table();

    // All three hash to index 4 (4 % 20 == 24 % 20 == 44 % 20 == 4)
    assert(h->insert(4, 40) == true);
    assert(h->insert(24, 240) == true);
    assert(h->insert(44, 440) == true);

    // Delete the middle element (24), leaving a tombstone at index 5
    h->delete(24);
    assert(h->get(24) == NULL);

    // Key 44 (at index 6) must still be reachable across the tombstone
    Node *n44 = h->get(44);
    assert(n44 != NULL && n44->value == 440);

    // Inserting a new colliding key (64) should recycle the tombstone at index 5
    assert(h->insert(64, 640) == true);
    assert(h->nodes[5] != NULL && h->nodes[5]->key == 64);
    assert(h->get(64)->value == 640);

    h->destroy();
    printf("[PASS] test_tombstone_chain_and_reuse\n");
}

void test_negative_keys(void)
{
    HashTable *h = make_hash_table();

    assert(h->insert(-5, 50) == true);
    assert(h->insert(-25, 250) == true); // Collides with -5

    assert(h->get(-5)->value == 50);
    assert(h->get(-25)->value == 250);

    h->delete(-5);
    assert(h->get(-5) == NULL);
    assert(h->get(-25)->value == 250);

    h->destroy();
    printf("[PASS] test_negative_keys\n");
}

void test_full_table_and_tombstone_saturation(void)
{
    HashTable *h = make_hash_table();

    // Fill all 20 slots
    for (int i = 0; i < SIZE; i++) {
        assert(h->insert(i, i * 10) == true);
    }

    // 21st distinct key must fail cleanly without infinite looping
    assert(h->insert(100, 1000) == false);

    // Updating an existing key must still succeed even when table is 100% full
    assert(h->insert(10, 999) == true);
    assert(h->get(10)->value == 999);

    // Delete every element so the table is 100% full of tombstones
    for (int i = 0; i < SIZE; i++) {
        h->delete(i);
    }

    // Lookup on a 100%-tombstone table must terminate cleanly and return NULL
    assert(h->get(10) == NULL);

    // Inserting into a 100%-tombstone table must reuse a tombstone slot
    assert(h->insert(77, 770) == true);
    assert(h->get(77)->value == 770);

    h->destroy();
    printf("[PASS] test_full_table_and_tombstone_saturation\n");
}

int main(int argc, char *argv[])
{
		test_basic_insert_and_get();
    test_update_existing_key();
    test_collisions_and_wrap_around();
    test_tombstone_chain_and_reuse();
    test_negative_keys();
    test_full_table_and_tombstone_saturation();
    printf("\nAll hash table unit tests passed!\n");
    return 0;
}
