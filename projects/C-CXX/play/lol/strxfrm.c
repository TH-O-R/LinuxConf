#include <stdio.h>
#include <string.h>

int main()
{
  char str1[20];
  char *str2 = "youssef";

  strxfrm(str1, str2, 3);
  
  printf("%s\n", str1);

  return 0;
}
