#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *nigga = fopen("lol.txt", "w");

  char msg[] = "\033[H";

  for (int i = 0; i <= 4; i++) {
    fprintf(nigga, "%c", msg[i]);
  }

  fclose(nigga);
  return 0;
}
