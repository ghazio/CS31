/*
 * Calls your assembly swap function.
 * You don't need to change this.
 */
#include<stdio.h>
#include<stdlib.h>

/* You will implement this functions in IA32 in the file swap.s */
void swap(int *x, int *y); // x and y are passed as pointers


int main(int argc, char *argv[]) {

  int a, b, res;

  if(argc != 3) {
    printf("usage: ./main a b\n");
    exit(1);
  }
  a = atoi(argv[1]);
  b = atoi(argv[2]);

  printf("before swap a = %d, b = %d\n",a,b);
  swap(&a, &b);
  printf("after swap a = %d, b = %d\n",a, b);
}
