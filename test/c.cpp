
#include <stdio.h>

int fun(int *data)
{
  (*data)++;
  return 0;
}

int main()
{
  int a = 3;
  fun(&a);
  printf("a=%d\n", a);
  return 0;
}