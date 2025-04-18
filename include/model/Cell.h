#ifndef __CELL_H
#define __CELL_H

enum class CellState { Hidden, Revealed, Flagged };

class Cell {
public:
    Cell();

    void reveal();
    void toggleFlag();
    bool isMine() const;
    void setMine(bool);

    CellState getState() const;
    int getAdjacentMines() const;
    void setAdjacentMines(int);

	bool isRevealed() const;
    void setRevealed(bool revealed);

	bool isFlagged() const;
    void setFlagged(bool flagged);

private:
    bool mine;
    int adjacentMines;
    CellState state;
	bool revealed;

};

#endif /* __CELL_H */
