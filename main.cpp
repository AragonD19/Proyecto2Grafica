#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <chrono>
#include "imageloader.h"
#include "raycaster.h"

SDL_Window* window;
SDL_Renderer* renderer;
bool hasWon = false;

void clear(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 56, 56, 56, 255);
    SDL_RenderClear(renderer);
}

void welcomeScreen(SDL_Renderer* renderer) {
    bool welcome = false;
    while (!welcome) {
        ImageLoader::render(renderer, "welcome_image", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                welcome = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    welcome = true; // Sal del bucle al presionar la barra espaciadora
                }
            }
        }
    }
}

void draw_floor(SDL_Renderer* renderer, Color floorColor, Color backgroundColor){
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_Rect backgroundRect = {
            0,
            0,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
    };
    SDL_RenderFillRect(renderer, &backgroundRect);
    SDL_SetRenderDrawColor(renderer, floorColor.r, floorColor.g, floorColor.b, floorColor.a);
    SDL_Rect floorRect = {
            0,
            SCREEN_HEIGHT / 2,
            SCREEN_WIDTH,
            SCREEN_HEIGHT / 2
    };
    SDL_RenderFillRect(renderer, &floorRect);
}

void loadMapAndRunGame(Raycaster& r, const std::string& mapFilePath) {
    r.load_map(mapFilePath);
    bool running = true;

    int frameCounter = 0;
    double totalTime = 0.0;
    int fps = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            if (r.has_won()) {
                hasWon = true;
                break;  // Exit the event loop to prevent further input
            }
            if (hasWon) {
                r.draw_victory_screen();
            }
            if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_LEFT:
                        r.player.a += 3.14 / 24;
                        break;
                    case SDLK_RIGHT:
                        r.player.a -= 3.14 / 24;
                        break;
                    case SDLK_UP:
                        r.sdlk_up();
                        break;
                    case SDLK_DOWN:
                        r.sdlk_down();
                        break;
                    default:
                        break;
                }
            }
        }


        clear(renderer);
        draw_floor(renderer, floorColor, myBackgroundColor);
        r.render();



        SDL_RenderPresent(renderer);

        auto endTime = std::chrono::high_resolution_clock::now();
        double frameTime = std::chrono::duration<double>(endTime - startTime).count();
        startTime = endTime;

        totalTime += frameTime;
        frameCounter++;

        if (totalTime >= 1.0) {
            fps = static_cast<int>(frameCounter);
            frameCounter = 0;
            totalTime = 0.0;
            std::string windowTitle = "SMT: Persona Labyrinth | FPS: " + std::to_string(fps);
            SDL_SetWindowTitle(window, windowTitle.c_str());
        }

    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    ImageLoader::init();

    window = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS);

    ImageLoader::loadImage("+", "../assets/wall10.png");
    ImageLoader::loadImage("-", "../assets/wall20.png");
    ImageLoader::loadImage("|", "../assets/wall30.png");
    ImageLoader::loadImage("*", "../assets/wall40.png");
    ImageLoader::loadImage("g", "../assets/exit0.png");
    ImageLoader::loadImage("welcome_image", "../assets/Titulo.jpg");
    ImageLoader::loadImage("win", "../assets/win.jpg");
    ImageLoader::loadImage("level_image", "../assets/level.jpg");

    Raycaster r = { renderer };



    bool running = true;
    welcomeScreen(renderer);
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImageLoader::render(renderer, "level_image", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        loadMapAndRunGame(r, "../assets/level1.txt");
                        break;
                    case SDLK_2:
                        loadMapAndRunGame(r, "../assets/level2.txt");
                        break;
                    case SDLK_3:
                        loadMapAndRunGame(r, "../assets/level3.txt");
                        break;
                }
            }

        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}