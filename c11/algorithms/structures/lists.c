#include <stdio.h>
#include <stdlib.h>

typedef struct linked_node {
  int value;
  struct linked_node *next;
} LinkedNode;

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
  void (*push)(int item);
  void (*prepend)(int item);
  void (*pop)();
  void (*shift)();
  DoubleLinkedNode (*find)(int item);
  void (*destroy)();
} List;

List *new() {
  List *l = (List *) malloc(sizeof(List));
  l->head = NULL;
  l->tail = NULL;
  l->size = 0;
  return l;
}

int list_length(List *list) {
  return list->size;
}

void list_push(List *l, int item) {
  DoubleLinkedNode *node =
    (DoubleLinkedNode *) malloc(sizeof(DoubleLinkedNode));

  node->value = item;
  node->next = NULL;
  if(l->tail != NULL) {
    node->prev = NULL;
    l->head = node;
  } else {
    node->prev = l->tail;
    l->tail->next = node;
  }
  l->tail = node;
  l->size++;
}

void list_pop(List *l) {
  if (l->tail != NULL && l->tail->prev != NULL) {
    l->tail->prev->next = NULL;
    l->tail = l->tail->prev;
    l->size--;
  } else {
    l->size = 0;
    l->tail = NULL;
    l->head = NULL;
  }
}

void list_destroy(List  *list) {
  while (list->length() > 0) {
    list->pop();
  }
  free(list);
}

DoubleLinkedNode *find(List *l, int item) {
  DoubleLinkedNode *current = l->head;
  while (current->next != NULL) {
    if (current->value == item) {
      return current;
    }
    current = current->next;
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  printf("1\n");
  List *lista = new();
  DoubleLinkedNode *node;
  lista->push = list_push;
  lista->push(lista, 1);
  lista->push(lista, 2);
  node = lista->find(1);
  return 0;
}
