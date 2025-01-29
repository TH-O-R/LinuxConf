#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define WIDTH 30
// #define HEIGHT 10
#define WIDTH 50
#define HEIGHT 30

int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int direction; // 0 = stop, 1 = left, 2 = right, 3 = up, 4 = down

void Setup() {
  gameOver = 0;
  direction = 0;
  x = WIDTH / 2;
  y = HEIGHT / 2;
  fruitX = rand() % WIDTH;
  fruitY = rand() % HEIGHT;
  score = 0;
}

void Draw() {
  clear(); // Clear the screen

  // Top border
  for (int i = 0; i < WIDTH + 2; i++)
    printw("#");
  printw("\n");

  // Field
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (j == 0)
        printw("#"); // Left border
      if (i == y && j == x)
        printw("O"); // Snake head
      else if (i == fruitY && j == fruitX)
        printw("*"); // Fruit
      else {
        int print = 0;
        for (int k = 0; k < nTail; k++) {
          if (tailX[k] == j && tailY[k] == i) {
            printw("o"); // Snake tail
            print = 1;
          }
        }
        if (!print)
          printw(" ");
      }

      if (j == WIDTH - 1)
        printw("#"); // Right border
    }
    printw("\n");
  }

  // Bottom border
  for (int i = 0; i < WIDTH + 2; i++)
    printw("#");
  printw("\n");

  // Score
  printw("Score: %d\n", score);
  refresh();
}

void Input() {
  timeout(100); // Set input timeout to 100ms
  int ch = getch();
  switch (ch) {
  case 'a':
    direction = 1;
    break; // Left
  case 'd':
    direction = 2;
    break; // Right
  case 'w':
    direction = 3;
    break; // Up
  case 's':
    direction = 4;
    break; // Down
  case ';':
    gameOver = 1;
    break; // Quit
  }
}

void Logic() {
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = x;
  tailY[0] = y;

  for (int i = 1; i < nTail; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  switch (direction) {
  case 1:
    x--;
    break; // Left
  case 2:
    x++;
    break; // Right
  case 3:
    y--;
    break; // Up
  case 4:
    y++;
    break; // Down
  }

  if (x >= WIDTH)
    x = 0;
  else if (x < 0)
    x = WIDTH - 1;
  if (y >= HEIGHT)
    y = 0;
  else if (y < 0)
    y = HEIGHT - 1;

  for (int i = 0; i < nTail; i++) {
    if (tailX[i] == x && tailY[i] == y)
      gameOver = 1;
  }

  if (x == fruitX && y == fruitY) {
    score += 10;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    nTail++;
  }
}

int main() {
  srand(time(NULL));
  initscr();            // Initialize ncurses
  curs_set(0);          // Hide cursor
  noecho();             // Don't display typed characters
  keypad(stdscr, TRUE); // Enable special keys

  Setup();

  while (!gameOver) {
    Draw();
    Input();
    Logic();
  }

  endwin(); // End ncurses mode

  printf("Game Over! Final Score: %d\n", score);
  return 0;
}
