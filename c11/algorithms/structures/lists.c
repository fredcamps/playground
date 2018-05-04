#include <stdio.h>
#include <stdlib.h>

typedef struct linked_node {
	int value;
	struct linked_node *next;
}   LinkedNode;

typedef struct double_linked_node {
	int value;
	struct double_linked_node *next;
	struct double_linked_node *prev;
} DoubleLinkedNode;

typedef struct list {
	int size;
	DoubleLinkedNode *head;
	DoubleLinkedNode *tail;
	int (*length)();
	void (*append)(int item);
	void (*prepend)(int item);
	void (*pop)();
	void (*shift)();
	void (*print)();
	void (*sort)();
	DoubleLinkedNode *(*find)(int item);
	void (*destroy)();
} List;

List *l;

int list_length() {
	return l->size;
}

void list_append(int item) {
	DoubleLinkedNode *node =
		(DoubleLinkedNode *) malloc(sizeof(DoubleLinkedNode));
	node->value = item;
	if (l->tail == NULL) {
		node->prev = node;
		node->next = node;
		l->head = node;
	} else {
		node->prev = l->tail;
		node->next = l->head;
		node->prev->next = node;
		node->next->prev = node;
	}
	l->tail = node;
	l->size++;
}

void list_pop() {
	if (l->length() > 1) {
		l->tail = l->tail->prev;
		l->tail->next = l->head;
		l->size--;
	} else {
		l->size = 0;
		free(l->tail);
		free(l->head);
	}
}

void list_prepend(int item) {
	DoubleLinkedNode *node =
		(DoubleLinkedNode *) malloc(sizeof(DoubleLinkedNode));

	/* Next step for implement */
}

void list_shift() {
	/* Not implemented yet */
}

void list_destroy() {
	while (l->length() > 0) {
		l->pop();
	}
	free(l);
}

void list_print() {
	int len = l->length();
	DoubleLinkedNode *current = l->head;
	DoubleLinkedNode *next = l->head->next;
	for (int i = 0; i < len; i++) {
		printf(" %d ", current->value);
		current = next;
		next = next->next;
	}
	printf(".\n");
}

DoubleLinkedNode *list_find(int item) {
	int len = l->length();
	DoubleLinkedNode *current = l->head;
	DoubleLinkedNode *next = l->head->next;
	for (int i = 0; i < len; i++) {
		if (current->value == item) {
			printf("Found %d ", current->value);
			return current;
		}
		current = next;
		next = next->next;
	}
	return NULL;
}

void list_sort() {
	/* Not Implemented Yet.	*/
}

List *make_list() {
	l = (List *) malloc(sizeof(List));
	l->print = list_print;
	l->append = list_append;
	l->prepend = list_prepend;
	l->pop = list_pop;
	l->destroy = list_destroy;
	l->length = list_length;
	l->find = list_find;
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

int main(int argc, char *argv[])
{
	List *l1 = make_list();
	List *l2 = make_list();
	// 	List *l3 = make_list();
	l1->append(2);
	l1->append(1);
	l1->append(3);
	l1->append(4);
	l1->print();
	l1->find(4);
    l1->find(1);
	l2->prepend(1);
	l2->prepend(2);
	l2->prepend(3);
	l2->prepend(4);
	l2->print();
	l1->destroy();
	l2->destroy();
	return 0;
}
