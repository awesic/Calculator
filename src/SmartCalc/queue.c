#include "queue_stack.h"

queue *init_queue() {
  queue *que = (queue *)malloc(sizeof(queue));
  que->head = que->tail = NULL;
  return que;
}

queue_node *init_queue_node(int id, double val) {
  queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
  new_node->val = val;
  new_node->id = id;
  new_node->next_node = NULL;
  return new_node;
}

void enqueue(queue *que, int id, double val) {
  queue_node *new_node = init_queue_node(id, val);
  if (que->head == NULL) {
    que->head = new_node;
  } else {
    que->tail->next_node = new_node;
  }
  que->tail = new_node;
}

void dequeue(queue *que) {
  if (que->head) {
    queue_node *tmp = que->head;
    que->head = que->head->next_node;
    free(tmp);
  }
}

void destroy_queue(queue *que) {
  while (que->head) dequeue(que);
  free(que);
}