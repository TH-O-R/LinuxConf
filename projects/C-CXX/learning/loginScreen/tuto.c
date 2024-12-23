#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

void set_terminal_raw_mode(int fd, struct termios *old_tio) {
    struct termios new_tio;

    // Get current terminal settings
    tcgetattr(fd, old_tio);

    // Copy current settings to new settings
    new_tio = *old_tio;


    // Disable canonical mode (no line buffering)
    new_tio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Disable echo, canonical mode, etc.
    
    // Set input modes (optional)
    new_tio.c_iflag &= ~(IXON | IXOFF | IXANY);  // Disable flow control
    new_tio.c_iflag &= ~ICRNL;                    // Prevent newline conversion

    // Set output modes (optional)
    new_tio.c_oflag &= ~OPOST; // Disable output processing

    // Set control modes (optional)
    new_tio.c_cflag |= (CLOCAL | CREAD); // Enable receiver

    // Set local modes
    new_tio.c_lflag &= ~(ECHO | ICANON); // Disable echo and canonical mode

    // Set the new terminal settings
    tcsetattr(fd, TCSANOW, &new_tio);
}

void reset_terminal(int fd, struct termios *old_tio) {
    // Restore previous terminal settings
    tcsetattr(fd, TCSANOW, old_tio);
}

int main() {
    struct termios old_tio;

    // Set terminal to raw mode
    set_terminal_raw_mode(STDIN_FILENO, &old_tio);

    char c;
    printf("Type a character (Press 'q' to quit):\n");

    // Read input character by character
    while (1) {
        c = getchar();  // Get a character
        if (c == 'q') {
            break;  // Quit when 'q' is pressed
        }
        printf("You pressed: %c\n", c);
    }

    // Reset the terminal to its original settings before exiting
    reset_terminal(STDIN_FILENO, &old_tio);
    
    return 0;
}
