#include "process.h"

node_d new_node_d(double num) {
  node_d n;
  n = (node_d)malloc(sizeof(node_double));
  n->num = num;
  n->prev = NULL;
  return n;
}

stack_d new_stack_d() {
  stack_d s;
  s = (stack_d)malloc(sizeof(stack_double));
  s->top = NULL;
  return s;
}

void add_stack_node_d(stack_d s, double num) {
  node_d n = new_node_d(num);
  n->prev = s->top;
  s->top = n;
}

node_double extract_stack_node_double(stack_d s) {
  node_double n = {0, NULL};
  if (s->top != NULL) {
    node_d aux;
    aux = s->top;
    s->top = s->top->prev;
    n = *aux;
    free(aux);
  }

  return n;
}

void destroy_stack_d(stack_d s) {
  while (s->top != NULL) {
    extract_stack_node_double(s);
  }
  free(s);
}

int is_empty_d(stack_d s) { return s->top == NULL; }

node_c new_node_c(char c) {
  node_c n;
  n = (node_c)malloc(sizeof(node_char));
  n->c = c;
  n->prev = NULL;
  return n;
}

stack_c new_stack_c() {
  stack_c s;
  s = (stack_c)malloc(sizeof(stack_char));
  s->top = NULL;
  return s;
}

void add_stack_node_c(stack_c s, char c) {
  node_c n = new_node_c(c);
  n->prev = s->top;
  s->top = n;
}

node_char extract_stack_node_char(stack_c s) {
  node_char n = {0, NULL};
  if (s->top != NULL) {
    node_c aux;
    aux = s->top;
    s->top = s->top->prev;
    n = *aux;
    free(aux);
  }

  return n;
}

void destroy_stack_c(stack_c s) {
  while (s->top != NULL) {
    extract_stack_node_char(s);
  }
  free(s);
}

int is_empty_c(stack_c s) { return s->top == NULL; }
