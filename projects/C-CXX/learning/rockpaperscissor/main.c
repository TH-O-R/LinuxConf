/*rock paper scissors game*/
/*one real player and one computer player*/
/*****************************
  * game details:
  * choose how many rounds  
  * choose how many COM players
*****************************/

#include <stdio.h>

int SAVE_PLAYERS()
{
  int com_nb; //number of computer players 

  printf("How many COM players to battle against: ");
  scanf("%d", &com_nb);

  return com_nb;
}

int PLAYER_CHOICE()
{
  int throw; // the choice of the player

  
  while (throw != 1 && throw != 2 && throw != 3) 
  {
  
    printf("\nChoose your next throw:\t(1) ROCK\t(2) PAPER\t(3) SCISSOR:\n");
  
    scanf("%d", &throw);
    
    switch (throw) 
    {
      case 1:
        printf("you chose rock!\n");
        break;
      case 2:
        printf("you chose paper!\n");
        break;
      case 3:
        printf("you chose scissor!\n");
        break;
      default:
        printf("please pick a valid option!\n");
        while (getchar() != '\0')
        break;
    }
  }
  
  return throw;
}

int main()
{
  int choice[3] = {1,2,3}; // 1 will be rock 2 will be paper and 3 will be scissor

  printf("WELCOME TO THE GREATEST ROCK PAPER SCISSORS GAME EVER!\n");

  int players = SAVE_PLAYERS();
  fflush(stdin);
  int throw = PLAYER_CHOICE();

  return 0;
}
