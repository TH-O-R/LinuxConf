#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
  printf("\033[H\033[J"); // Clear the screen

  // Get the username and hostname
  char *user = getlogin();
  if (user == NULL) {
    fprintf(stderr, "Couldn't get the username!\n");
    return 1;
  }

  char host[50];
  if (gethostname(host, sizeof(host)) != 0) {
    fprintf(stderr, "Couldn't get the hostname!\n");
    return 1;
  }

  char command[1024];
  printf("[\033[32m%s @ %s\033[0m] $ ", user, host);
  fgets(command, sizeof(command), stdin);

  // Remove the newline character from command if it exists
  command[strcspn(command, "\n")] = '\0';

  // Construct the full command path
  char full_com[2024] = "/bin/";
  if (strlen(command) + 5 < sizeof(full_com)) {  // 5 bytes for "/bin/" and null terminator
    strcat(full_com, command);
  } else {
    fprintf(stderr, "Command too long!\n");
    return 1;
  }

  printf("Executing: %s\n", full_com);

  // Execute the command
  if (execl(full_com, full_com, NULL) == -1) {
    perror("execl failed");
    return 1;
  }

  return 0;
}

