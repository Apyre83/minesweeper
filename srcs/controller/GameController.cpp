#include "controller/GameController.h"
#include <iostream>

GameController::GameController(int w, int h, int mines) : grid(w, h, mines) {}


void GameController::onCellClicked(int x, int y) {
    if (!grid.isValid(x, y)) return;

    Cell& cell = grid.getCell(x, y);
    if (cell.isRevealed()) return;

    lastClickedX = x;
    lastClickedY = y;

    if (!grid.minesPlaced) {
        grid.placeMinesAvoiding(x, y);
        grid.calculateAdjacents();
        grid.minesPlaced = true;
    }

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
    if (!undoStack.empty()) {
        undoStack.top()->undo();
        redoStack.push(std::move(undoStack.top()));
        undoStack.pop();
    }
}

void GameController::redo() {
    if (!redoStack.empty()) {
        redoStack.top()->execute();
        undoStack.push(std::move(redoStack.top()));
        redoStack.pop();
    }
}

void GameController::executeCommand(std::unique_ptr<Command> cmd) {
    cmd->execute();
    undoStack.push(std::move(cmd));
    while (!redoStack.empty()) redoStack.pop();
}

Grid& GameController::getGrid() { return grid; }

