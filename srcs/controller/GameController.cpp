#include "controller/GameController.h"
#include <iostream>

GameController::GameController(int w, int h, int mines) : grid(w, h, mines), undo_grid(grid), redo_grid(grid), w(w), h(h), mines(mines) {}


void GameController::onCellClicked(int x, int y) {

	undo_grid = grid;

    if (!grid.minesPlaced) {
		grid.placeMinesAvoiding(x, y);
		grid.calculateAdjacents();
		grid.minesPlaced = true;
	}

    if (!grid.isValid(x, y)) return;

    Cell& cell = grid.getCell(x, y);
    if (cell.isRevealed()) {
		std::cout << "cell at x = " << x << " and y = " << y << " is revealed" << std::endl;
		return;
	}

    lastClickedX = x;
    lastClickedY = y;




    if (cell.isMine()) {
        grid.revealAllMines();
        gameOver = true;
        return;
    }

    if (cell.getAdjacentMines() == 0) {
        grid.floodReveal(x, y);
    } else {
        cell.setRevealed(true);
    }
}




void GameController::undo() {
    redo_grid = grid;
    can_redo = true;

    grid = undo_grid;

	undo_grid = Grid(w, h, mines);
}

void GameController::redo() {
    if (!can_redo) return;

    undo_grid = grid;

    grid = redo_grid;
    can_redo = false;
}

Grid& GameController::getGrid() { return grid; }

