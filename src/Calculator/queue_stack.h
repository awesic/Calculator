#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H

#include <stdlib.h>

typedef struct queue_node_s {
  struct queue_node_s *next_node;
  int id;
  double val;
} queue_node;

typedef struct squeue {
  queue_node *head;
  queue_node *tail;
} queue;

queue *init_queue();
queue_node *init_queue_node(int id, double val);
void dequeue(queue *que);
void enqueue(queue *que, int id, double val);
void destroy_queue(queue *que);

//---------------------------------------------------

typedef struct stack_node_s {
  struct stack_node_s *prev_node;
  int id;
  double val;
} stack_node;

typedef struct sstack {
  stack_node *end_node;
} stack;

stack *init_stack();
stack_node *init_stack_node(int id, double val);
void push(stack *st, int id, double val);
void pop(stack *st);
void destroy_stack(stack *st);

#endif  // QUEUE_STACK_H