#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROW 15
#define COL 15

int grid[ROW][COL] = {0};

void init_state();
int count_nbh(int row, int col);
void next_gen();
void print_gen();

int main(void) {
    srand(time(NULL));

    system("clear");
    init_state();
    while(1) {
        print_gen();
        next_gen();
        printf("\e[1H");
        sleep(1);
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
