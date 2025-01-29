#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define WIDTH 1920
#define HEIGHT 1080

// Physical properties
const float G = 9.81f; // Gravitational constant
const float PI = 3.14159265358979f;

// Pendulum parameters
float m1 = 1.0f, m2 = 1.0f;                   // Masses
float l1 = 200.0f, l2 = 200.0f;               // Lengths
float theta1 = PI / 2.0f, theta2 = PI / 2.0f; // Initial angles
float theta1_vel = 0.0f, theta2_vel = 0.0f;   // Velocities

float dt = 0.11f; // Time step default: 0.1f

// Function to compute the angular acceleration
void compute_forces(float *a1, float *a2) {
  float delta = theta2 - theta1;
  float denom1 = (m1 + m2) * l1 - m2 * l1 * cos(delta) * cos(delta);
  float denom2 = (l2 / l1) * denom1;

  // Equations for angular accelerations
  *a1 = (m2 * l2 * theta2_vel * theta2_vel * sin(delta) * cos(delta) +
         m2 * G * sin(theta2) * cos(delta) +
         m2 * l2 * theta2_vel * theta2_vel * sin(delta) -
         (m1 + m2) * G * sin(theta1)) /
        denom1;

  *a2 = (m2 * l2 * theta2_vel * theta2_vel * sin(delta) * cos(delta) +
         (m1 + m2) * G * sin(theta1) * cos(delta) -
         (m1 + m2) * l1 * theta1_vel * theta1_vel * sin(delta) -
         (m1 + m2) * G * sin(theta2)) /
        denom2;
}

// Function to update the state of the pendulum
void update(float *theta1, float *theta2, float *theta1_vel,
            float *theta2_vel) {
  float a1, a2;
  compute_forces(&a1, &a2);

  *theta1_vel += a1 * dt;
  *theta2_vel += a2 * dt;

  *theta1 += *theta1_vel * dt;
  *theta2 += *theta2_vel * dt;
}

// Custom function to draw a filled circle
void SDL_RenderFillCircle(SDL_Renderer *renderer, int cx, int cy, int r) {
  for (int w = 0; w < r * 2; w++) {
    for (int h = 0; h < r * 2; h++) {
      int dx = r - w; // horizontal offset
      int dy = r - h; // vertical offset
      if (dx * dx + dy * dy <= r * r) {
        SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
      }
    }
  }
}

// Function to draw the pendulum using SDL2
void draw_pendulum(SDL_Renderer *renderer, float x1, float y1, float x2,
                   float y2) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
  SDL_RenderFillCircle(renderer, (int)x2, (int)y2,
                       10); // Draw the second pendulum mass
}

// function to render rays from the second pendulum ball
void draw_rays(SDL_Renderer *renderer, float x2, float y2, int num_rays,
               int ray_length) {
  // Set Blending mode for transperancy
  SDL_SetRenderDrawBlendMode(renderer,
                             SDL_BLENDMODE_BLEND); // Enable alpha blending

  for (int i = 0; i < num_rays; i++) {
    // calculate the angle for each ray
    float angle = (i * 2.0f * PI) / num_rays; // Spread rays around the Ball

    // calculate the end point of the ray
    int end_x = (int)(x2 + ray_length * cos(angle));
    int end_y = (int)(y2 + ray_length * sin(angle));

    // calculate the distance between the origin and the end of the ray
    float distance =
        sqrt((end_x - x2) * (end_x - x2) + (end_y - y2) * (end_y - y2));

    // calculate the alpha based on the distance (LOW TAPER FADE YEAH!)
    int alpha =
        255 - (int)(255 * (distance / ray_length)); // Fade from 255 to 0

    // Ensure alpha stays based on the distance
    if (alpha < 0) {
      alpha = 0;
    }

    // Set the color with fading alpha
    SDL_SetRenderDrawColor(renderer, 255, 255, 0,
                           alpha); // Yellow Rays + fading alpha

    // Draw the ray as a line from the second ball positions
    SDL_RenderDrawLine(renderer, (int)x2, (int)y2, end_x, end_y);
  }

  // Reset blending mode after drawing the rays
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); // Disable it
}

// Function to Handle user input
void handle_input(SDL_Event *event) {
  // Key controls to modify parameters during runtime
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_w: // increase Length of pendulum 1
      l1 += 10;
      break;
    case SDLK_s: // decrease Length of pendulum 1
      if (l1 > 10)
        l1 -= 10;
      break;
    case SDLK_a: // increase Length of pendulum 2
      l2 += 10;
      break;
    case SDLK_d: // Decrease Length of pendulum 2
      if (l2 > 10)
        l2 -= 10;
      break;
    case SDLK_UP: // Increase mass of pendulum 1
      m1 += 0.1f;
      break;
    case SDLK_DOWN: // Decrease mass of pendulum 1
      if (m1 > 0.1f)
        m1 -= 0.1f;
      break;
    case SDLK_RIGHT: // Increase mass of pendulum 2
      m2 += 0.1f;
      break;
    case SDLK_LEFT: // Decrease mass of pendulum 2
      if (m2 > 0.1f)
        m2 -= 0.1f;
      break;
    case SDLK_ESCAPE: // Quit on Esc
      exit(0);
      break;
    }
  }
}

// function to render the current parameters on the screen
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text,
                 int x, int y) {
  SDL_Color textColor = {255, 255, 255, 255}; // White

  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);

  int textWidth = textSurface->w;
  int textHeight = textSurface->h;
  SDL_Rect renderQuad = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
}

// Main function
int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  if (TTF_Init() == -1) {
    fprintf(stderr, "SDL_ttf ERROR: %s\n", TTF_GetError());
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("Double Pendulum Simulation", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Load font
  TTF_Font *font = TTF_OpenFont(
      "/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf", 24);
  if (!font) {
    fprintf(stderr, "TTF_OpenFont ERROR: %s\n", TTF_GetError());
    return 1;
  }

  // Initial position calculation
  float x1 = WIDTH / 2 + l1 * sin(theta1);
  float y1 = HEIGHT / 4 + l1 * cos(theta1);

  float x2 = x1 + l2 * sin(theta2);
  float y2 = y1 + l2 * cos(theta2);

  // Main loop
  int running = 1;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }

      // Handle user input for controls
      handle_input(&event);
    }

    // Update the physics of the pendulum
    update(&theta1, &theta2, &theta1_vel, &theta2_vel);

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Update pendulum positions
    x1 = WIDTH / 2 + l1 * sin(theta1);
    y1 = HEIGHT / 4 + l1 * cos(theta1);

    x2 = x1 + l2 * sin(theta2);
    y2 = y1 + l2 * cos(theta2);

    // Draw the pendulum
    draw_pendulum(renderer, WIDTH / 2, HEIGHT / 4, x1, y1);
    draw_pendulum(renderer, x1, y1, x2, y2);

    // Draw light Rays from the second pendulum ball
    draw_rays(renderer, x2, y2, 600, 500); // 36 rays and 150 pixels for Length

    // renderer the parameters text on screen
    char infoText[256];
    snprintf(infoText, sizeof(infoText),
             "m1: %.2f (up/down), m2: %.2f (right/left)| l1: %.2f (w/s), l2: "
             "%.2f (a/d)| "
             "theta1: %.2f , theta2: %.2f ",
             m1, m2, l1, l2, theta1, theta2);
    render_text(renderer, font, infoText, 10, 10);

    // Present the rendered frame
    SDL_RenderPresent(renderer);

    // Delay for the next frame
    SDL_Delay(7);
  }

  // Clean up
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_Quit();

  return 0;
}
