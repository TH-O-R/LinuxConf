#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Function to clear the screen and move the cursor to the top
void clear_screen() {
    printf("\033[H\033[J"); // Clear screen and reset cursor to top
}

// Function to print combinations up to the current substring
void print_combinations(char *prefix, char *message, int length) {
    for (char c = 'A'; c <= message[length - 1]; c++) {
        // Create the combination by appending the current character to the prefix
        printf("%s%c", prefix, c);  // Print the combination (e.g., HA->, HB->, ...)
        fflush(stdout); // Flush output buffer to ensure it appears immediately
        usleep(35000); // Delay for animation effect (0.15 seconds)
        clear_screen(); // Clear screen for next output
    }
    // Print the final combination (without the '->' at the end)
    /*printf("%s%c\n", prefix, message[length - 1]);*/
}

// Function to build and print the combinations progressively
void progressive_print(char *message) {
    int length = strlen(message);

    // Iterate through each character in the message
    for (int i = 1; i <= length; i++) 
    {
        char prefix[i + 1]; // Create space for the current prefix

        // Copy the first i characters from the message to the prefix
        for (int j = 0; j < i; j++) 
	{
            prefix[j] = message[j];
        }
        prefix[i] = '\0'; // Null-terminate the prefix string

        // Print combinations for the current prefix
        print_combinations(prefix, message, i);
    }
}

int main(void) {
    // The target message to be progressively revealed
    char message[] = "\033[32mTODAY'S MISSION:\n \033[31m KILL YOUSSEF BENTALEB \033[0m";
    
    // Start printing the progressive combinations
    progressive_print(message);

    // Finally, print the complete message
    printf("%s\n", message);

    return 0;
}

