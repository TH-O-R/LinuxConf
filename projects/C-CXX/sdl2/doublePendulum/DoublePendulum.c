#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

// Physical properties
const float G = 9.81f;  // Gravitational constant
const float PI = 3.14159265358979f;

// Pendulum parameters
float m1 = 1.0f, m2 = 1.0f;   // Masses
float l1 = 200.0f, l2 = 200.0f; // Lengths
float theta1 = PI / 2.0f, theta2 = PI / 2.0f;  // Initial angles
float theta1_vel = 0.0f, theta2_vel = 0.0f; // Velocities

float dt = 0.11f; // Time step default: 0.1f

// Function to compute the angular acceleration
void compute_forces(float* a1, float* a2) {
    float delta = theta2 - theta1;
    float denom1 = (m1 + m2) * l1 - m2 * l1 * cos(delta) * cos(delta);
    float denom2 = (l2 / l1) * denom1;

    // Equations for angular accelerations
    *a1 = (m2 * l2 * theta2_vel * theta2_vel * sin(delta) * cos(delta) +
           m2 * G * sin(theta2) * cos(delta) +
           m2 * l2 * theta2_vel * theta2_vel * sin(delta) -
           (m1 + m2) * G * sin(theta1)) / denom1;

    *a2 = (m2 * l2 * theta2_vel * theta2_vel * sin(delta) * cos(delta) +
           (m1 + m2) * G * sin(theta1) * cos(delta) -
           (m1 + m2) * l1 * theta1_vel * theta1_vel * sin(delta) -
           (m1 + m2) * G * sin(theta2)) / denom2;
}

// Function to update the state of the pendulum
void update(float* theta1, float* theta2, float* theta1_vel, float* theta2_vel) {
    float a1, a2;
    compute_forces(&a1, &a2);

    *theta1_vel += a1 * dt;
    *theta2_vel += a2 * dt;

    *theta1 += *theta1_vel * dt;
    *theta2 += *theta2_vel * dt;
}

// Custom function to draw a filled circle
void SDL_RenderFillCircle(SDL_Renderer* renderer, int cx, int cy, int r) {
    for (int w = 0; w < r * 2; w++) {
        for (int h = 0; h < r * 2; h++) {
            int dx = r - w;  // horizontal offset
            int dy = r - h;  // vertical offset
            if (dx * dx + dy * dy <= r * r) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

// Function to draw the pendulum using SDL2
void draw_pendulum(SDL_Renderer* renderer, float x1, float y1, float x2, float y2) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    SDL_RenderFillCircle(renderer, (int)x2, (int)y2, 10);  // Draw the second pendulum mass
}

// Main function
int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Double Pendulum Simulation",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
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
        }

        // Update the physics of the pendulum
        update(&theta1, &theta2, &theta1_vel, &theta2_vel);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 76, 210, 160, 255);
        SDL_RenderClear(renderer);

        // Update pendulum positions
        x1 = WIDTH / 2 + l1 * sin(theta1);
        y1 = HEIGHT / 4 + l1 * cos(theta1);

        x2 = x1 + l2 * sin(theta2);
        y2 = y1 + l2 * cos(theta2);

        // Draw the pendulum
        draw_pendulum(renderer, WIDTH / 2, HEIGHT / 4, x1, y1);
        draw_pendulum(renderer, x1, y1, x2, y2);

        // Present the rendered frame
        SDL_RenderPresent(renderer);

        // Delay for the next frame
        SDL_Delay(7);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

