#include <stdio.h>
#include <stdlib.h>

void plustwo(int one, int two);

int main(int argc, char const *argv[]) {
  /* code */
  int one = atoi(argv[1]);
  int two = atoi(argv[2]);
  plustwo(one, two);
  return 0;
}

void plustwo(int one, int two) {
  int t = one + two;
  printf("(%d) + (%d) = %d\n",one, two, t);
}
