#include "model/Grid.h"
#include <cstdlib>
#include <ctime>

Grid::Grid(int w, int h, int m) : width(w), height(h) {
    reset(w, h, m);
}

void Grid::reset(int w, int h, int mines) {
    width = w;
    height = h;
    totalMines = mines;
    cells = std::vector<std::vector<Cell>>(width, std::vector<Cell>(height));
    minesPlaced = false;
}


void Grid::placeMines(int count) {
    std::srand(std::time(nullptr));
    while (count > 0) {
        int x = std::rand() % width;
        int y = std::rand() % height;
        if (!cells[x][y].isMine()) {
            cells[x][y].setMine(true);
            count--;
        }
    }
}

void Grid::placeMinesAvoiding(int safeX, int safeY) {
    int count = totalMines;
    std::srand(std::time(nullptr));

    while (count > 0) {
        int x = std::rand() % width;
        int y = std::rand() % height;

        // Skip the 3x3 region around the first clicked cell
        if (std::abs(x - safeX) <= 1 && std::abs(y - safeY) <= 1)
            continue;

        if (!cells[x][y].isMine()) {
            cells[x][y].setMine(true);
            count--;
        }
    }
}


void Grid::calculateAdjacents() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int count = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx, ny = y + dy;
                    if (isValid(nx, ny) && cells[nx][ny].isMine())
                        count++;
                }
            }
            cells[x][y].setAdjacentMines(count);
        }
    }
}

Cell& Grid::getCell(int x, int y) { return cells[x][y]; }
bool Grid::isValid(int x, int y) const { return x >= 0 && x < width && y >= 0 && y < height; }
int Grid::getWidth() const { return width; }
int Grid::getHeight() const { return height; }


bool Grid::isRevealed(int x, int y) const {
    // Check if the cell at (x, y) is revealed
    return cells[x][y].isRevealed();  // Assuming Cell class has an isRevealed() method
}

bool Grid::hasWon() const {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            const Cell& cell = cells[x][y];
            if (!cell.isMine() && !cell.isRevealed()) {
                return false;
            }
        }
    }
    return true;
}


void Grid::floodReveal(int x, int y) {
    if (!isValid(x, y) || cells[x][y].isRevealed() || cells[x][y].isMine())
        return;

    cells[x][y].setRevealed(true);

    if (cells[x][y].getAdjacentMines() > 0)
        return;  // stop at numbered cell

    // recurse to neighbors
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx != 0 || dy != 0) {
                floodReveal(x + dx, y + dy);
            }
        }
    }
}


void Grid::revealAllMines() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (cells[x][y].isMine()) {
                cells[x][y].setRevealed(true);
            }
        }
    }
}

