/* TODO:
 *  -allow users to sign in or sign up
 *  -the password should be hidden
 *  -in case of too many failed attempts lock the user
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ATTEMPTS 3
#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

struct users {
  char email[MAX_EMAIL_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  int locked;
};

int signin(struct users* user)
{
  char email[MAX_EMAIL_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  int attempts = 0;


  while (attempts < MAX_ATTEMPTS)
  {
    printf("\n\033[H \033[JWelcome to the sign in page\n");

    printf("\nEnter your E-mail: ");
    /*fscanf(stdin, "%s", email);*/
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    if (strcmp(email, user->email) == 0 && user->locked)
    {
      printf("\nYou can't login! \033[31m{locked}\033[0m\n");
      return 0;
    }
    else if (strcmp(email, user->email) != 0)
    {
      printf("\nthis user does not exist!\n");
      return 0;
    }

    printf("\nEnter your password: ");
    /*fscanf(stdin, "%s", password);*/
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if(strcmp(email, user->email) == 0 && strcmp(password, user->password) == 0)
    {
      printf("\nSign in COMPLETE !\n");
      return 1;
    }
    else
    {
      attempts++;
    }
  }
  user->locked = 1;
  printf("\nUser \033[31m{locked}\033[0m for too many failed attempts\n");
  return 0;
}

int signup(struct users* user)
{
  char email[MAX_EMAIL_LENGTH];
  char password[MAX_PASSWORD_LENGTH];

  printf("\n\033[H\033[JWelcome to the sign up page\n");

  printf("\nEnter your E-mail: ");
  /*fscanf(stdin, "%s", email);*/
  fgets(email, sizeof(email), stdin);
  email[strcspn(email, "\n")] = '\0';

  printf("\nEnter your password: ");
  /*fscanf(stdin, "%s", password);*/
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = '\0';

  strncpy(user->email, email, MAX_EMAIL_LENGTH - 1);
  strncpy(user->password, password, MAX_PASSWORD_LENGTH - 1);
  user->locked = 0;

  user->email[MAX_EMAIL_LENGTH - 1] = '\0';
  user->password[MAX_PASSWORD_LENGTH - 1] = '\0';

  printf("\n\033[32mSign up Successful\033[0m\n");

  return 1;
}

int main()
{
  int choice;
  char ch[100];
  
  struct users user;
  memset(&user, 0, sizeof(user));


  while(1)
  {
    printf("\nWelcome to this login screen please choose: \n1-Sign in via email.\n2-Sign up via email.\n");
    fgets(ch, sizeof(ch), stdin);
    choice = atoi(ch);

    switch (choice) 
    {
      case 1:
        signin(&user);
        break;
      case 2:
        signup(&user);
        break;
      default:
        printf("\nPlease choose a valid option!\n");
        break;
    }
  }
  
  return 0;
}
