#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 350

#define ROW 30
#define COL 30

int grid[ROW][COL] = {0};

void init_state();
int count_nbh(int row, int col);
void next_gen();
void print_gen();

SDL_Window* window;
SDL_Renderer* renderer;

bool is_running;

int main(void) {
    srand(time(NULL));

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    int wr = SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    if(wr < 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    is_running = true;
    init_state();
    while(is_running) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 255);
        SDL_RenderClear(renderer);

        print_gen();
        next_gen();

        SDL_RenderPresent(renderer);

        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                is_running = false;
            }
        }
    }

    return 0;
}

void init_state() {
    for(int i = 0; i < ROW; ++i) {
        for(int j = 0; j < COL; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

void print_gen() {
    for(int i = 0; i < ROW; ++i) {
        for(int j = 0; j < COL; j++) {
            if(grid[i][j] == 1) {
                printf("0");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int count_nbh(int r, int c) {
    int nbh = 0;

    for(int i = r - 1; i <= r + 1; ++i) {
        for(int j = c - 1; j <= c + 1; ++j) {
            if((i == r && j == c) || (i >= ROW || j >= COL) || (i < 0 || j < 0)) continue;
             
            if(grid[i][j] == 1) {
                nbh++;
            }
        }
    }

    return nbh;
}

void next_gen() {
    for(int i = 0; i < ROW; ++i) {
        for(int j = 0; j < COL; j++) {
            int nbh = count_nbh(i, j);

            if(grid[i][j] == 1 && (nbh == 2 || nbh == 3)) {
                grid[i][j] = 1;
            } else if(grid[i][j] == 0 && nbh == 3) { 
                grid[i][j] = 1;
            } else {
                grid[i][j] = 0;
            }
        }
    }
}
