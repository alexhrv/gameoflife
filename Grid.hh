#ifndef GRID_HH
#define GRID_HH

#include <vector>

class Grid {

public:
    Grid(int size);
    Grid(int sizeX, int sizeY);

    int countNeighbours(int x, int y);
    void evolve();
    void fillWithZeroes();
    bool isAlive(int x, int y);
    bool isInBounds(int x, int y);
    void randomize();
    int sizeX() {return sizeX_;}
    int sizeY() {return sizeY_;}
    void toggleCell(int x, int y);

private:
    int sizeX_;
    int sizeY_;
    std::vector<std::vector<bool>> grid_;
};

#endif