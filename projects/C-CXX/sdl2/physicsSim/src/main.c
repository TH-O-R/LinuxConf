#include "physics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int WIDTH = 1280;
int HEIGHT = 720;
#define GRAVITY 9.81

void SDL_RenderFillCircle(SDL_Renderer *rend, int x0, int y0, int radius) {
  // Uses the midpoint circle algorithm to draw a filled circle
  // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
  int x = radius;
  int y = 0;
  int radiusError = 1 - x;
  while (x >= y) {
    SDL_RenderDrawLine(rend, x + x0, y + y0, -x + x0, y + y0);
    SDL_RenderDrawLine(rend, y + x0, x + y0, -y + x0, x + y0);
    SDL_RenderDrawLine(rend, -x + x0, -y + y0, x + x0, -y + y0);
    SDL_RenderDrawLine(rend, -y + x0, -x + y0, y + x0, -x + y0);
    y++;
    if (radiusError < 0)
      radiusError += 2 * y + 1;
    else {
      x--;
      radiusError += 2 * (y - x + 1);
    }
  }
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window =
      SDL_CreateWindow("Physics Simulator", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  RigidBody body1 = {{200, 100}, {50, 50}, {0, 0}, 1.0f, 25.0f};
  RigidBody body2 = {{400, 100}, {-50, 50}, {0, 0}, 1.0f, 25.0f};

  int running = 1;
  Uint32 lastTime = SDL_GetTicks();

  while (running) {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
    }

    // Physics update
    apply_gravity(&body1, GRAVITY);
    apply_gravity(&body2, GRAVITY);

    update_physics(&body1, deltaTime);
    update_physics(&body2, deltaTime);

    // Collision detection and response
    handle_collision(&body1, &body2);

    // Render the scene
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw bodies as circles
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillCircle(renderer, body1.position.x, body1.position.y,
                         body1.radius);
    SDL_RenderFillCircle(renderer, body2.position.x, body2.position.y,
                         body2.radius);

    SDL_RenderPresent(renderer);
    SDL_Delay(16); // ~60 fps
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
