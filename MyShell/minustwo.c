#include <stdio.h>
#include <stdlib.h>

void minustwo(int one, int two);

int main(int argc, char const *argv[]) {
  /* code */
  int one = atoi(argv[1]);
  int two = atoi(argv[2]);
  minustwo(one, two);
  return 0;
}

void minustwo(int one, int two) {
  int t = one - two;
  printf("(%d) - (%d) = %d\n",one, two, t);
}
