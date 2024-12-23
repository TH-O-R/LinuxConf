#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *message = "\033[32mTODAY'S MISSION:\n\033[31m KILL ALL ENEMIES\033[0m";
	
  //first we clear the screen
	printf("\033[H\033[J");

	for (int i=0; message[i] != '\0'; i++)
	{
		char letter = message[i];

		for (char j='A'; j <= letter; j++)
		{
      int k = 0;
      do 
        {
          printf("%c", message[k]);
          k++;
        } while (k < i);
			
      printf("%c", j);
			fflush(stdout);

 			//300 000 microseconds->0.3 seconds 
			usleep(95000);
			printf("\033[H");
		}
	}
  
	return 0;
}
