#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/spinbutton.h>
#include "CellButton.h"
#include "../controller/GameController.h"





#define TEXT_HELP "La règle du jeu est relativement simple, et nous est donnée par wikipédia : un champ de mines est représenté par une grille en deux dimensions. Chaque case de la grille peut soit cacher une mine, soit être vide. Le but du jeu est de découvrir toutes les cases libres sans faire exploser les mines, c’est-à-dire sans cliquer sur les cases qui les dissimulent. Lorsque le joueur clique sur une case libre comportant au moins une mine dans l’une de ses cases avoisinantes, un chiffre apparaît, indiquant ce nombre de mines. Si en revanche toutes les cases adjacentes sont vides, une case vide est affichée et la même opération est répétée sur ces cases, et ce jusqu’à ce que la zone vide soit entièrement délimitée par des chiffres. Lorsque le joieur pense qu’il y a une mine, il peut placer un drapeau sur la case pour signaler sa position. En comparant les différentes informations récoltées, le joueur peut ainsi progresser dans le déminage du terrain. S’il se trompe et clique sur une mine, il a perdu."




class MainWindow : public Gtk::Window {
public:
    MainWindow(GameController* controller);
    void update();

private:
	GameController* controller;
    Gtk::Box vbox;
    Gtk::Grid grid;

    Gtk::Button undoButton;
    Gtk::Button redoButton;
    Gtk::Button helpButton;
    Gtk::Button restartButton;

    void onCellClicked(int x, int y);
    void buildGrid();

	int lastClickedX = -1;
	int lastClickedY = -1;


	void updateUndoRedoButtons();

	bool	hasWon = false;
};


#endif /* __MAINWINDOW_H */
