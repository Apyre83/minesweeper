#ifndef __GAMECONTROLLER_H
#define __GAMECONTROLLER_H

#include "../model/Grid.h"
#include "../utils/Command.h"
#include <stack>
#include <memory>

class GameController {
public:
    GameController(int w, int h, int mines);
    void onCellClicked(int x, int y);
    void undo();
    void redo();

    Grid& getGrid();

	int getLastClickedX() const { return lastClickedX; }
	int getLastClickedY() const { return lastClickedY; }



private:
    Grid grid;
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;

    void executeCommand(std::unique_ptr<Command> cmd);

	int	lastClickedX = -1;
	int	lastClickedY = -1;

	bool	gameOver = false;
};

#endif /* __GAMECONTROLLER_H */
