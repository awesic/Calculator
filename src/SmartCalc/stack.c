#include "queue_stack.h"

stack *init_stack() {
  stack *new_stack = (stack *)calloc(1, sizeof(stack));
  new_stack->end_node = NULL;
  return new_stack;
}

stack_node *init_stack_node(int id, double val) {
  stack_node *new_node = (stack_node *)calloc(1, sizeof(stack_node));
  new_node->id = id;
  new_node->val = val;
  new_node->prev_node = NULL;
  return new_node;
}

void push(stack *st, int id, double val) {
  stack_node *new_node = init_stack_node(id, val);
  new_node->prev_node = st->end_node;
  st->end_node = new_node;
}

void pop(stack *st) {
  stack_node *tmp = NULL;
  if (st->end_node) {
    tmp = st->end_node->prev_node;
    free(st->end_node);
    st->end_node = tmp;
  }
}

void destroy_stack(stack *st) {
  while (st->end_node) pop(st);
  free(st);
}