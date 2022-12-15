#include "process.h"

int main() {
  int flag = 1;
  char string[150];
  if (input(string) == -1) {
    flag = -1;
  }
  if (flag == 1 && check(string) == 1) {
    char *postfix = polish(string);
    output(postfix);
    free(postfix);
  } else {
    printf("n/a");
  }
  return 0;
}
