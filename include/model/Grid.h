#ifndef __GRID_H
#define __GRID_H


#include "Cell.h"
#include <vector>

class Grid {
public:
    Grid(int width, int height, int mines);
    void reset(int width, int height, int mines);

    Cell& getCell(int x, int y);
    bool isValid(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

	bool isRevealed(int x, int y) const;

	bool hasWon() const;

	void floodReveal(int x, int y);

	void revealAllMines();


	void placeMinesAvoiding(int safeX, int safeY);

	bool	minesPlaced;

    void calculateAdjacents();

private:
    int width, height;
    std::vector<std::vector<Cell>> cells;
	int	totalMines;

    void placeMines(int count);

};



#endif /* __GRID_H */
