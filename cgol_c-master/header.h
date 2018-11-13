#ifndef MYHEADER_H_
#define MYHEADER_H_

#define red     "\x1b[31m"
#define green   "\x1b[32m"
#define yellow  "\x1b[33m"
#define blue    "\x1b[34m"
#define white   "\x1b[107m"
#define cyan    "\x1b[36m"
#define reset   "\x1b[0m"

typedef unsigned char bool;
typedef unsigned char byte;
typedef struct cell
{
    bool isAlive;
    byte neighbors;
} cell;

void printGrid(cell **grid, int n);
void simulate(cell **grid, int n);
void updateNeighborCount(cell **grid, int n);
int countNeighbors(cell **grid, int n, int x, int y);
cell **createGrid(int n);
void fillZero(cell **grid, int n);
void fillRandom(cell **grid, int n);
void freeGrid(cell **grid, int n);

#endif