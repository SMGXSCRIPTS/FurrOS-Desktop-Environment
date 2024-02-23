#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CUBE_SIZE = 20;

struct Cube {
    int x, y;
    int velocity;
};

int main() {
    srand(time(nullptr));
    std::cout << "Dam.OS FurrOS Easter Egg Initilizing...\n";
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "ERROR! Failed To Initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Physics Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "ERROR! Failed To Create Window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "ERROR! Failed To Create Renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    const int NUM_CUBES = 5;
    Cube cubes[NUM_CUBES];
    for (int i = 0; i < NUM_CUBES; ++i) {
        cubes[i].x = rand() % (WINDOW_WIDTH - CUBE_SIZE);
        cubes[i].y = 0;
        cubes[i].velocity = rand() % 5 + 1;
    }

    bool RENDERER_RUNTIME = true;
    while (RENDERER_RUNTIME == true) {
        SDL_Event SDL_EVENT;
        while (SDL_PollEvent(&SDL_EVENT)) {
            if (SDL_EVENT.type == SDL_QUIT) {
                RENDERER_RUNTIME = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NUM_CUBES; ++i) {
            cubes[i].y += cubes[i].velocity;
            if (cubes[i].y > WINDOW_HEIGHT) {
                cubes[i].y = 0;
                cubes[i].x = rand() % (WINDOW_WIDTH - CUBE_SIZE);
                cubes[i].velocity = rand() % 5 + 1;
            }
            SDL_Rect rect = { cubes[i].x, cubes[i].y, CUBE_SIZE, CUBE_SIZE };
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}