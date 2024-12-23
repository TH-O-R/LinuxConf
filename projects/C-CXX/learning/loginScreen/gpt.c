#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MAX_ATTEMPTS 3
#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define FILE_NAME "user_data.dat"

// Struct to store user data
struct users {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int locked; // 0 = not locked, 1 = locked
};

// Function to hide password input with asterisks
void hide_password(char* password, size_t max_len) {
    struct termios oldt, newt;
    int ch, i = 0;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO; // Disable echoing input (password will be hidden)
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("Enter your password(for security reasons the password is hidden): ");
    while (i < max_len - 1 && (ch = getchar()) != '\n' && ch != EOF) {
        if (ch == 127 || ch == 8) {  // Handle backspace
            if (i > 0) {
                printf("\b \b"); // Move cursor back and overwrite with space
                i--;
            }
        } else {
            password[i++] = ch;
            printf("*"); // Print an asterisk for each character entered
        }
    }
    password[i] = '\0'; // Null terminate the string

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\n");
}

// Function to load user data from file
int load_user_data(struct users* user) {
    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        return 0; // No data file exists, no user data to load
    }
    fread(user, sizeof(struct users), 1, file);
    fclose(file);
    return 1;
}

// Function to save user data to file
void save_user_data(const struct users* user) {
    FILE* file = fopen(FILE_NAME, "wb");
    if (file != NULL) {
        fwrite(user, sizeof(struct users), 1, file);
        fclose(file);
    }
}

// Sign-in function
int signin(struct users* user)
{
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int attempts = 0;

    printf("\n\033[H\033[JWelcome to the sign-in page\n");
    
    while (attempts < MAX_ATTEMPTS)
    {

        // Prompt for email
        printf("\nEnter your E-mail: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0'; // Remove the newline character

        // Check if account is locked
        if (user->locked)
        {
            printf("\nYou can't login! Account is \033[31m{locked}\033[0m\n");
            return 0;
        }

        // Prompt for password
        hide_password(password, sizeof(password)); // Hide password input

        // Compare email and password
        if (strcmp(email, user->email) == 0 && strcmp(password, user->password) == 0)
        {
            printf("\nSign-in COMPLETE!\n");
            return 1; // Successful sign-in
        }
        else
        {
            printf("\nInvalid email or password. Attempt %d of %d\n", attempts + 1, MAX_ATTEMPTS);
            attempts++;
        }
    }

    // Lock the account after too many failed attempts
    user->locked = 1;
    printf("\nUser account \033[31m{locked}\033[0m for too many failed attempts\n");
    save_user_data(user); // Save user data after locking
    return 0; // Account is locked
}

// Sign-up function
int signup(struct users* user)
{
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\n\033[H\033[JWelcome to the sign-up page\n");

    // Prompt for email
    printf("\nEnter your E-mail: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0'; // Remove the newline character

    // Prompt for password
    hide_password(password, sizeof(password)); // Hide password input

    // Store email and password
    strncpy(user->email, email, MAX_EMAIL_LENGTH - 1);
    strncpy(user->password, password, MAX_PASSWORD_LENGTH - 1);

    // Ensure null-termination
    user->email[MAX_EMAIL_LENGTH - 1] = '\0';
    user->password[MAX_PASSWORD_LENGTH - 1] = '\0';

    user->locked = 0; // Account starts unlocked

    save_user_data(user); // Save user data to file
    printf("\nSign-up successful! You can now sign in with your credentials.\n");
    return 1;
}

int main()
{
    int choice;
    char ch[100];

    struct users user;
    memset(&user, 0, sizeof(user)); // Initialize user data to zero

    // Load user data from file if available
    if (!load_user_data(&user)) {
        printf("\nNo existing user data found. Please sign up.\n");
    }

    while (1)
    {
        printf("\nWelcome to this login screen. Please choose: \n1-Sign in via email.\n2-Sign up via email.\n");
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

