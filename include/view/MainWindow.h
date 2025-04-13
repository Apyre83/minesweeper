#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include "CellButton.h"
#include "../controller/GameController.h"

class MainWindow : public Gtk::Window {
public:
    MainWindow(GameController& controller);
    void update();

private:
    GameController& controller;
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


};


#endif /* __MAINWINDOW_H */
