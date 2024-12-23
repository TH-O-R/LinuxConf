#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 128

void render_password(SDL_Renderer *renderer, TTF_Font *font, const char *password, SDL_Color color, int x, int y) {
    //check if passwd is empty
    if (strlen(password) == 0)
    {
        return; //no passwd no render!
    }

    // Create a string with '*' characters for each password character
    char maskedPassword[MAX_PASSWORD_LENGTH];
    memset(maskedPassword, '*', strlen(password));
    maskedPassword[strlen(password)] = '\0';  // Null-terminate the string

    // Create a texture from the masked password string
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, maskedPassword, color);
    if (textSurface == NULL) {
        printf("Error creating text surface: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (textTexture == NULL) {
        printf("Error creating text texture: %s\n", SDL_GetError());
        return;
    }

    // Render the text (the masked password) at the specified position
    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    /*SDL_Rect textRect = {x, y, w, h};*/
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    //free resources
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize TTF (for text rendering)
    if (TTF_Init() == -1) {
        printf("SDL_ttf Initialization failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("SDL2 Password Input", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create an SDL renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Load font
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/Hack-Bold.ttf", 24);
    if (!font) {
        printf("Font loading failed: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Set up text color (black)
    SDL_Color color = { 255, 0, 0, 255 };

    // Main event loop
    SDL_Event e;
    int quit = 0;
    char password[MAX_PASSWORD_LENGTH] = "";
    int passwordLength = 0;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    // Password input finished (Enter pressed)
                    printf("Password entered: %s\n", password);
                }
                else if (e.key.keysym.sym == SDLK_BACKSPACE && passwordLength > 0) {
                    // Remove last character
                    password[--passwordLength] = '\0';
                }
                else if (e.key.keysym.sym >= SDLK_SPACE && e.key.keysym.sym <= SDLK_z) {
                    // Add the typed character to the password
                    if (passwordLength < MAX_PASSWORD_LENGTH - 1) {
                        password[passwordLength++] = (char)e.key.keysym.sym;
                        password[passwordLength] = '\0'; // Null-terminate the string
                    }
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render the password (masked with *)
        render_password(renderer, font, password, color, 100, 100);

        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    // Clean up
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
