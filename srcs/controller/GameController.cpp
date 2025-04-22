#include "controller/GameController.h"
#include <iostream>

GameController::GameController(int w, int h, int mines) : grid(w, h, mines), undo_grid(grid), redo_grid(grid), w(w), h(h), mines(mines) {}


void GameController::onCellClicked(int x, int y) {
    if (!grid.minesPlaced) {
		grid.placeMinesAvoiding(x, y);
		grid.calculateAdjacents();
		grid.minesPlaced = true;
	}

    if (!grid.isValid(x, y)) return;

    Cell& cell = grid.getCell(x, y);
    if (cell.isRevealed()) { return; }

	undo_grid = grid;
	can_undo = true;

    lastClickedX = x;
    lastClickedY = y;

    if (cell.isMine()) {
        grid.revealAllMines();
        gameOver = true;
        return;
    }

    if (cell.getAdjacentMines() == 0) { grid.floodReveal(x, y); }
	else { cell.setRevealed(true); }
}


void GameController::onCellRightClicked(int x, int y) {
    if (!grid.isValid(x, y)) return;

    Cell& cell = grid.getCell(x, y);
    if (cell.isRevealed()) return;

    undo_grid = grid;
	can_undo = true;

	cell.setFlagged(!cell.isFlagged());
}

void GameController::undo() {
	if (can_undo == false) return;
    redo_grid = grid;
    can_redo = true;

    grid = undo_grid;

	undo_grid = Grid(w, h, mines);
	can_undo = false;
}

void GameController::redo() {
    if (!can_redo) return;

    undo_grid = grid;
	can_undo = true;

    grid = redo_grid;
    can_redo = false;
}

Grid& GameController::getGrid() { return grid; }
