#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 10
#define COL 10

int grid[ROW][COL] = {0};

void init_state();
int count_nbh();
void next_gen();
void print_gen();

int main(void) {
    srand(time(NULL));

    init_state();
    print_gen();

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
