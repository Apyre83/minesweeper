#include "model/Cell.h"

Cell::Cell() : mine(false), adjacentMines(0), state(CellState::Hidden), revealed(false) {}

void Cell::reveal() {
    if (state == CellState::Hidden)
        state = CellState::Revealed;
}

void Cell::toggleFlag() {
    if (state == CellState::Hidden)
        state = CellState::Flagged;
    else if (state == CellState::Flagged)
        state = CellState::Hidden;
}

bool Cell::isMine() const { return mine; }
void Cell::setMine(bool value) { mine = value; }
CellState Cell::getState() const { return state; }
int Cell::getAdjacentMines() const { return adjacentMines; }
void Cell::setAdjacentMines(int count) { adjacentMines = count; }

bool Cell::isRevealed() const {
    return revealed;
}

void Cell::setRevealed(bool r) {
    revealed = r;
}

bool Cell::isFlagged() const {
	return state == CellState::Flagged;
}

void Cell::setFlagged(bool f) {
	if (f == true && revealed == false) {
		state = CellState::Flagged;
	}
	else if (f == false && state == CellState::Flagged) {
		state = CellState::Hidden;
	}
}
