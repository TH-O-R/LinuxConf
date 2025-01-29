#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int choice;
  while (choice != 10) {
    printf("pick one of the "
           "commands:\n1-ls\n2-pwd\n3-fastfetch\n4-fetch\n10-quit\nYour "
           "pick: ");
    scanf("%d", &choice);

    pid_t pid = fork();

    if (pid > 0) {
      waitpid(0, NULL, WUNTRACED);
    }

    else if (pid == 0) {

      if (choice == 1) {
        printf("\n");
        execl("/bin/ls", "-a");
        printf("\n");
      } else if (choice == 2) {
        printf("\n");
        execl("/bin/pwd", NULL);
        printf("\n");
      } else if (choice == 3) {
        printf("\n");
        execl("/bin/fastfetch", NULL);
        printf("\n");
      } else if (choice == 4) {
        printf("\n");
        execl("/usr/local/bin/fetch", NULL);
        printf("\n");
      } else if (choice == 5) {
        printf("\n");
        execl("/usr/bin/pacman", "-Syu", NULL);
      } else {
        fprintf(stderr, "ERROR!\n");
      }
    }
  }
}
