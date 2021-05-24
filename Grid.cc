#include <stdlib.h>
#include <time.h>

#include "Grid.hh"

/**
 * Structure that holds cell's information and handling methods
 *
 */
Grid::Grid(int size):
    sizeX_(size), sizeY_(size) {

    fillWithZeroes();
}

Grid::Grid(int sizeX, int sizeY):
    sizeX_(sizeX), sizeY_(sizeY) {

    fillWithZeroes();
}

/**
 * Counts number of alive cells in surrounding 8 cells.
 *
 */
int
Grid::countNeighbours(int x, int y) {
    int sum = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int nbX = x + i;
            int nbY = y + j;
            // dont check if out of bounds pixels and (0,0) point
            if (!isInBounds(nbX, nbY) || (i == 0 && j == 0)) {
                continue;
            }
            if (isAlive(nbX, nbY)) {
                sum++;
            }
        }
    }
    return sum;
}

/**
 * Counts neighbours, and generates new evolution of cells.
 *
 */
void
Grid::evolve() {
    std::vector<std::vector<bool>>
        nextGrid(sizeY(), std::vector<bool> (sizeX(), false));

    int neighbours = 0;
    for (int i = 0; i < sizeX(); i++) {
        for (int j = 0; j < sizeY(); j++) {
            neighbours = countNeighbours(i, j);
            // alive cell
            if (isAlive(i, j)) {
                // death by solitude
                if (neighbours < 2) {
                    nextGrid[i][j] = false;
                // death by over population
                } else if (neighbours > 3) {
                    nextGrid[i][j] = false;
                // stay alive
                } else {
                    nextGrid[i][j] = true;
                }
            // dead cell
            } else {
                if (neighbours == 3) {
                    nextGrid[i][j] = true;
                }
            }
        }
    }
    grid_ = nextGrid;
}

/**
 * Creates grid full of dead cells
 *
 */
void
Grid::fillWithZeroes() {
    std::vector<std::vector<bool>>
        zeroGrid(sizeY(), std::vector<bool> (sizeX(), false));
    grid_ = zeroGrid;
}

/**
 * Checks wherether cell is alive
 *
 */
bool
Grid::isAlive(int x, int y) {
    if (isInBounds(x, y)) {
        return grid_[x][y];
    } else {
        // TODO: smarter error handling
    }
}

/**
 * Gamegrid boundary checking helper method
 *
 */
bool
Grid::isInBounds(int x, int y) {
    return !(x < 0 || y < 0 || x > (sizeX() - 1) || y > (sizeY() - 1));
}

/**
 * Randomly fills grid with true or false
 *
 */
void
Grid::randomize() {
    srand(time(NULL));
    for (int i = 0; i < sizeX(); i++) {
        for (int j = 0; j < sizeY(); j++) {
            grid_[i][j] = rand() % 2;
        }
    }
}

/**
 * Turns cell alive or dead, based on current condition
 *
 */
void
Grid::toggleCell(int x, int y) {
    if (!isInBounds(x, y)) {
        return;
    }

    if (isAlive(x, y)) {
        grid_[x][y] = false;
    } else {
        grid_[x][y] = true;
    }
}
