#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fl = fopen("lol.txt", "w");

  char msg[] = "\033[H";
  
  for (int i=0; i <= 4; i++) {
    fprintf(fl, "%c", msg[i]);
  }
  
  fclose(fl);
  return 0;
}
