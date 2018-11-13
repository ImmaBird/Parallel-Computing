#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "header.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    if(argc < 2){
        printf("USAGE: command grid_size");
        return 1;
    }
    int n = atoi(argv[1]);
    cell **grid = createGrid(n);
    fillZero(grid, n);
    fillRandom(grid, n);
    int count = 0;
    while (3)
    {
        printf("Generation %d\n", count);
        simulate(grid, n);
        printGrid(grid, n);
        sleep(1);
        count++;
        printf("\n");
    }

    freeGrid(grid, n);
}

void printGrid(cell **grid, int n)
{
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (grid[x][y].isAlive)
            {
                printf(white " " reset);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void simulate(cell **grid, int n)
{
    updateNeighborCount(grid, n);
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            grid[x][y].isAlive = (grid[x][y].neighbors == 3) || (grid[x][y].isAlive && grid[x][y].neighbors == 2);
        }
    }
}

void updateNeighborCount(cell **grid, int n)
{
    for (int x = 1; x < n - 1; x++)
    {
        for (int y = 1; y < n - 1; y++)
        {
            grid[x][y].neighbors = countNeighbors(grid, n, x, y);
        }
    }
}

int countNeighbors(cell **grid, int n, int x, int y)
{
    int count = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            count += grid[i][j].isAlive;
        }
    }
    count -= grid[x][y].isAlive;
    return count;
}

cell **createGrid(int n)
{
    cell **grid = malloc(n * sizeof(grid));
    for (int i = 0; i < n; i++)
    {
        grid[i] = malloc(n * sizeof(cell));
    }
    return grid;
}

void fillZero(cell **grid, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            grid[i][j].isAlive = 0;
            grid[i][j].neighbors = 0;
        }
    }
}

void fillRandom(cell **grid, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            grid[i][j].isAlive = rand() > RAND_MAX/2;
            grid[i][j].neighbors = 0;
        }
    }
}

void freeGrid(cell **grid, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(grid[i]);
    }
    free(grid);
}