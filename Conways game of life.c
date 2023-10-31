#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 20
#define COLS 40

int grid[ROWS][COLS];
int nextGrid[ROWS][COLS];

void initializeGrid() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }
}

void displayGrid() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grid[i][j] == 1) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int countNeighbours(int row, int col) {
    int count = 0;
    int i, j;
    for (i = row - 1; i <= row + 1; i++) {
        for (j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && j >= 0 && i < ROWS && j < COLS) {
                count += grid[i][j];
            }
        }
    }
    count -= grid[row][col]; // Exclude the current cell itself
    return count;
}

void updateGrid() {
    int i, j, neighbours;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            neighbours = countNeighbours(i, j);
            if (grid[i][j] == 1) {
                // Cell is alive
                if (neighbours < 2 || neighbours > 3) {
                    nextGrid[i][j] = 0; // Dies due to underpopulation or overpopulation
                } else {
                    nextGrid[i][j] = 1; // Lives to the next generation
                }
            } else {
                // Cell is dead
                if (neighbours == 3) {
                    nextGrid[i][j] = 1; // Becomes alive due to reproduction
                }
            }
        }
    }

    // Copy nextGrid back to grid
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            grid[i][j] = nextGrid[i][j];
        }
    }
}

int main() {
    initializeGrid();
    grid[9][10] = 1;
    grid[10][11] = 1;
    grid[11][9] = 1;
    grid[11][10] = 1;
    grid[11][11] = 1;

    while (1) {
        system("clear"); // Clear the console
        displayGrid();
        updateGrid();
        usleep(100000); // Delay for a smoother visualization
    }

    return 0;
}