#ifndef __GAMECONTROLLER_H
#define __GAMECONTROLLER_H

#include "../model/Grid.h"
#include <stack>
#include <stdbool.h>

class GameController {
public:
    GameController(int w, int h, int mines);
    void onCellClicked(int x, int y);
	void onCellRightClicked(int x, int y);
    void undo();
    void redo();

    Grid& getGrid();

	int getLastClickedX() const { return lastClickedX; }
	int getLastClickedY() const { return lastClickedY; }


	bool	get_can_undo(void) const { return can_undo; }
	bool	get_can_redo(void) const { return can_redo; }


private:
    Grid	grid;
	Grid	undo_grid;
	Grid	redo_grid;
	bool	can_redo = false; /* Can only redo if he pressed undo as last action */
	bool	can_undo = false; /* Can only only once */

	int	w, h, mines;


	int	lastClickedX = -1;
	int	lastClickedY = -1;

	bool	gameOver = false;
};

#endif /* __GAMECONTROLLER_H */
