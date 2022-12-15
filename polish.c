#include "process.h"

double dijk_algorithm(char *postfix, double x) {
  stack_d d = new_stack_d();
  int counter = 0;
  for (int i = 0; i < (int)strlen(postfix); i++) {
    char c = postfix[i];
    if (is_digit(c)) {
      if (c != 'x') {
        char *str_number = parse_int(postfix, &i);
        char *ptr;
        double num = strtod(str_number, &ptr);

        add_stack_node_d(d, num);
        free(str_number);
      } else {
        add_stack_node_d(d, x);
      }
    } else if (priority(c) != -1) {
      counter += 1;
      if (c == '~') {
        double last;
        if (is_empty_d(d))
          last = 0;
        else
          last = extract_stack_node_double(d).num;
        add_stack_node_d(d, arithmetic('-', 0, last));

        continue;
      }
      double second;
      if (is_empty_d(d))
        second = 0;
      else
        second = extract_stack_node_double(d).num;

      double first;
      if (is_empty_d(d))
        first = 0;
      else if (c != 's' && c != 'c' && c != 't' && c != 'g' && c != 'l')
        first = extract_stack_node_double(d).num;
      else
        first = 0;
      add_stack_node_d(d, arithmetic(c, first, second));
    }
  }
  double result = extract_stack_node_double(d).num;
  destroy_stack_d(d);
  return result;
}

double arithmetic(char operation, double num1, double num2) {
  double result = 0;
  if (operation == '+') {
    result = num1 + num2;
  } else if (operation == '-') {
    result = num1 - num2;
  } else if (operation == '*') {
    result = num1 * num2;
  } else if (operation == '/') {
    result = num1 / num2;
  } else if (operation == '^') {
    result = pow(num1, num2);
  } else if (operation == 's') {
    result = sin(num2);
  } else if (operation == 'c') {
    result = cos(num2);
  } else if (operation == 't') {
    result = tan(num2);
  } else if (operation == 'g') {
    result = cos(num2) / sin(num2);
  } else if (operation == 'q') {
    result = pow(num2, 0.5);
  } else if (operation == 'l') {
    result = log(num2);
  }
  return result;
}

char *polish(char *infix) {
  char *postfix = malloc(strlen(infix) * sizeof(char) * 2);
  int n = 0;
  stack_c s = new_stack_c();
  for (int i = 0; i < (int)strlen(infix); i++) {
    char c = infix[i];
    if (is_digit(c)) {
      char *temp = parse_int(infix, &i);
      for (int j = 0; j < (int)strlen(temp); j++) {
        postfix[n] = temp[j];
        n++;
      }
      postfix[n] = ' ';
      n++;
      free(temp);
    } else if (c == '(') {
      add_stack_node_c(s, '(');
    } else if (c == ')') {
      while (!is_empty_c(s) && s->top->c != '(') {
        postfix[n] = extract_stack_node_char(s).c;
        n++;
        postfix[n] = ' ';
        n++;
      }
      extract_stack_node_char(s);
    } else if (priority(c) != -1) {
      char operation = c;
      if (operation == '-' &&
          (i == 0 || (i > 1 && priority(infix[i - 1]) != -1)))
        operation = '~';
      while (!is_empty_c(s) && priority(s->top->c) >= priority(operation)) {
        postfix[n] = extract_stack_node_char(s).c;
        n++;
        postfix[n] = ' ';
        n++;
      }
      if (operation == 'c' && infix[i + 1] == 'o') {
        add_stack_node_c(s, 'c');
      } else if (operation == 'c' && infix[i + 1] == 't') {
        add_stack_node_c(s, 'g');
      } else if (operation == 's' && infix[i + 1] == 'q') {
        add_stack_node_c(s, 'q');
      } else if (operation == 'l') {
        add_stack_node_c(s, 'l');
      } else {
        add_stack_node_c(s, operation);
      }

      if ((operation == 's' && infix[i + 1] == 'i') || operation == 'c' ||
          operation == 't' || operation == 'g') {
        i += 2;
      } else if (operation == 's' && infix[i + 1] == 'q') {
        i += 3;
      } else if (operation == 'l') {
        i += 1;
      }
    }
  }

  while (!is_empty_c(s)) {
    postfix[n] = extract_stack_node_char(s).c;
    n++;
  }
  destroy_stack_c(s);
  return postfix;
}

void output(char *postfix) {
  char board[max_y][max_x];

  for (int y = 0; y < max_y; y++) {
    for (int x = 0; x < max_x; x++) {
      board[y][x] = ' ';
    }
  }
  for (int x = 0; x < max_x; x++) {
    int y = round(-12 * dijk_algorithm(postfix, (4 * M_PI / 79) * x) + 12);
    if (y >= 0 && y <= 24) {
      board[y][x] = '.';
    }
  }
  for (int y = 0; y < max_y; y++) {
    for (int x = 0; x < max_x; x++) {
      printf("%c", board[y][x]);
    }
    printf("\n");
  }
}

int is_digit(char c) { return ('0' <= c && c <= '9') || (c == 'x'); }

int priority(char c) {
  int op_prior = -1;
  if (c == '(') {
    op_prior = 0;
  } else if (c == '+' || c == '-') {
    op_prior = 1;
  } else if (c == '*' || c == '/') {
    op_prior = 2;
  } else if (c == '^' || c == 's' || c == 'c' || c == 't' || c == 'g' ||
             c == 'q' || c == 'l') {
    op_prior = 3;
  } else if (c == '~') {
    op_prior = 4;
  }
  return op_prior;
}

char *parse_int(char *expr, int *pos) {
  char *str_number = NULL;
  int size = 0;
  for (; *pos < (int)strlen(expr); (*pos)++) {
    char num = expr[*pos];
    if (is_digit(num) || num == '.') {
      size++;

      char *temp = (char *)realloc(str_number, sizeof(char) * size);
      if (temp != NULL) str_number = temp;

      str_number[size - 1] = num;
    } else {
      (*pos)--;
      break;
    }
  }
  char *temp = (char *)realloc(str_number, sizeof(char) * ++size);
  if (temp != NULL) str_number = temp;
  if (str_number) str_number[size - 1] = '\0';
  return str_number;
}

int input(char string[150]) {
  int flag = 1;
  if (fgets(string, 150, stdin) == NULL) {
    flag = -1;
  }
  if (flag == 1) {
    int len = 0;
    for (; string[len] != '\0'; len++) {
    }
    string[len - 1] = '\0';
    if (len < 2 || len > 150) {
      flag = -1;
    }
  }
  return flag;
}

int check(char string[150]) {
  int flag = 1;
  char *correct = "0123456789.sincotargqlx()+-*/^ ";
  int len = strlen(string);
  for (int i = 0; i < len; i++) {
    if (strchr(correct, string[i]) == NULL) {
      flag = -1;
      break;
    }
  }
  return flag;
}