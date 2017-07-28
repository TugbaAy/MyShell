#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  int n = atoi(argv[1]);
  int i;
  long f = 1;

  if (n < 0){
    printf("Eksi değer girdiniz!");
  }
  else{
    for(i=1; i<=n; ++i){
      f *= i;
    }
    printf("%d! = %ld \n", n, f);
  }
  return 0;
}
