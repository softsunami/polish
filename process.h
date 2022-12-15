#ifndef SRC_PROCESS_H
#define SRC_PROCESS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_y 25
#define max_x 80
#define M_PI 3.1415926

char *polish(char *infix);
double arithmetic(char operation, double num1, double num2);
double dijk_algorithm(char *postfix, double x);

char *parse_int(char *expr, int *pos);
int priority(char c);
int input(char string[150]);
int check(char string[150]);
int is_digit(char c);
void output(char *postfix);

typedef struct node_char {
  char c;
  struct node_char *prev;
} node_char;

typedef node_char *node_c;

typedef struct stack_char {
  node_c top;
} stack_char;

typedef stack_char *stack_c;

node_c new_node_c(char c);
stack_c new_stack_c();
void add_stack_node_c(stack_c s, char c);
node_char extract_stack_node_char(stack_c s);
void destroy_stack_c(stack_c s);
int is_empty_c(stack_c s);

typedef struct node_double {
  double num;
  struct node_double *prev;
} node_double;

typedef node_double *node_d;

typedef struct stack_double {
  node_d top;
} stack_double;

typedef stack_double *stack_d;

node_d new_node_d(double num);
stack_d new_stack_d();
void add_stack_node_d(stack_d s, double num);
node_double extract_stack_node_double(stack_d s);
void destroy_stack_d(stack_d s);
int is_empty_d(stack_d s);

#endif  // SRC_PROCESS_H
