#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char lol[14] = "NIGGA NIGGA N";
  char ng[100];

  scanf("%c", ng);
  printf("%d\n", strcspn(lol, "A"));
  
  int ch = atoi(ng);
  printf("%d\n", ch);

  return 0;
}
