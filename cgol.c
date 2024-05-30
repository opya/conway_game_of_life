#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ROWS 30
#define COLS 60 
#define CLEAR_SCREEN() printf("\e[1;1H\e[2J")
#define DRAW_DEAD_CELL() printf(" ")
#define DRAW_LIVE_CELL() printf("#")

int cells[ROWS][COLS] = {0};

void gen_random_population(void);
void draw_grid(void);
int neighbors(int i, int j);

int main(void)
{
    int new_cells[ROWS][COLS] = {0};

    gen_random_population();

    CLEAR_SCREEN();

    while(1) {
        draw_grid();

        memcpy(&new_cells, cells, sizeof(cells));

        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j++) {
                int live_cells = neighbors(i, j);

                if(live_cells == 3)
                    new_cells[i][j] = 1;

                if(live_cells < 2 || live_cells > 3)
                    new_cells[i][j] = 0;

                live_cells = 0;
            }
        }

        memcpy(&cells, &new_cells, sizeof(new_cells));
        usleep(1000 * 50);
    }

    return 0;
}

void gen_random_population(void)
{
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            cells[i][j] = rand() % 2;
        }
    }

    // glader
    //cells[0][1] = 1;
    //cells[1][2] = 1;
    //cells[2][0] = 1;
    //cells[2][1] = 1;
    //cells[2][2] = 1;
}

void draw_grid(void)
{
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            (cells[i][j] == 1) ? DRAW_LIVE_CELL() : DRAW_DEAD_CELL();
        }
        printf("\n");
    }

    CLEAR_SCREEN();
}

int neighbors(int i, int j)
{
    int live_neighbors = 0;

    // top left
    if(i != 0 && j != 0 && cells[i - 1][j - 1] == 1) live_neighbors += 1;
    // top
    if(i != 0 && cells[i-1][j] == 1) live_neighbors += 1;
    // top right
    if(i != 0 && j < COLS && cells[i - 1][j + 1] == 1) live_neighbors += 1;

    // left
    if(j != 0 && cells[i][j-1] == 1) live_neighbors += 1;
    // right 
    if(j < COLS && cells[i][j+1] == 1) live_neighbors += 1;

    // bottom left
    if(i < ROWS && j != 0 && cells[i+1][j-1] == 1) live_neighbors += 1;
    // bottom
    if(i < ROWS && cells[i+1][j] == 1) live_neighbors += 1;
    // bottom right
    if(i < ROWS && j < COLS && cells[i+1][j+1] == 1) live_neighbors += 1;

    return live_neighbors;
}