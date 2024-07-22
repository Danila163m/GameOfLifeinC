#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 20
#define COLS 20

void initialize_grid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

void print_grid(int grid[ROWS][COLS]) {
    printf("\033[H"); // Move the cursor to the top-left corner of the screen
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(grid[i][j] ? "O" : " ");
        }
        printf("\n");
    }
    fflush(stdout);
}

int count_neighbors(int grid[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

void update_grid(int grid[ROWS][COLS]) {
    int new_grid[ROWS][COLS] = {0};
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = count_neighbors(grid, i, j);
            if (grid[i][j] == 1 && (neighbors == 2 || neighbors == 3)) {
                new_grid[i][j] = 1;
            } else if (grid[i][j] == 0 && neighbors == 3) {
                new_grid[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}

int main() {
    int grid[ROWS][COLS];
    initialize_grid(grid);
    printf("\033[2J"); // Clear the screen
    for (int i = 0; i < 100; i++) {
        print_grid(grid);
        update_grid(grid);
        usleep(100000);
    }
    return 0;
}

