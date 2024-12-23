#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("updating!!\n");
  /*execl("/bin/ls", "ls", "-l", "-a", NULL);*/
  execv("/bin/sudo", "/bin/pacman", "-Sy", NULL);
  return 0;
}
