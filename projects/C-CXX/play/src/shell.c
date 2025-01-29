#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
  printf("\033[H\033[J"); // Clear the screen
  char *user = getlogin();
  if (user == NULL) {
    fprintf(stderr, "couldn't get username!\n");
    return 1;
  }
  char host[50];
  if (gethostname(host, 10) != 0) {
    fprintf(stderr,"couldn't get the hostname!\n");
    return 1;
  }

  char command[1024];
  while(1) {
    printf("[\033[32m%s @ %s\033[0m] $ ", user, host);
    fgets(command, sizeof(command), stdin);

    command[strcspn(command, "\n")] = '\0';

    char full_com[sizeof(command)+6] = "/bin/";
    strcat(full_com, command);

    pid_t forkReturn = fork();
    if (forkReturn == 0) {
     if (execl(full_com, full_com, NULL) == -1) {
        fprintf(stderr, "\033[31mError:\033[0m Can't find this command!\n");
      }
    }
    else if (forkReturn > 0) {
      wait(0);
    }
    else {
      fprintf(stderr, "Couldn't create a new process!\n");
    }
  }
  return 0;
}
