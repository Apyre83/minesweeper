#include "view/MainWindow.h"
#include <gtkmm/messagedialog.h>
#include <iostream>

MainWindow::MainWindow(GameController& c) : controller(c), vbox(Gtk::ORIENTATION_VERTICAL),
    undoButton("Undo"), redoButton("Redo"), helpButton("Help"), restartButton("Restart") {

    set_title("Minesweeper");
    set_border_width(10);

    undoButton.signal_clicked().connect([this]() { 
        std::cout << "Undo button clicked" << std::endl;
        controller.undo(); 
        update(); 
    });

    redoButton.signal_clicked().connect([this]() { 
        std::cout << "Redo button clicked" << std::endl;
        controller.redo(); 
        update(); 
    });

    helpButton.signal_clicked().connect([]() {
        Gtk::MessageDialog dialog("Help:", false, Gtk::MESSAGE_INFO);
        dialog.set_secondary_text("Click cells to reveal them. Right-click to flag. Avoid the mines!");
        dialog.run();
    });

    restartButton.signal_clicked().connect([this]() {
        std::cout << "Restart button clicked" << std::endl;
        controller.getGrid().reset(10, 10, 10);
        buildGrid();
    });

    vbox.pack_start(undoButton);
    vbox.pack_start(redoButton);
    vbox.pack_start(helpButton);
    vbox.pack_start(restartButton);
    vbox.pack_start(grid);

    add(vbox);
    buildGrid();
    show_all_children();
}

void MainWindow::buildGrid() {
    std::cout << "Building grid..." << std::endl;

    int w = controller.getGrid().getWidth();
    int h = controller.getGrid().getHeight();
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            if (grid.get_child_at(x, y) == nullptr) {
                auto button = Gtk::make_managed<CellButton>(x, y);

                button->signal_clicked().connect([this, x, y]() {
                    const Cell& cell = controller.getGrid().getCell(x, y);
                    std::cout << "Left-clicked (" << x << ", " << y << ")"
                              << " | Mine: " << (cell.isMine() ? "yes" : "no")
                              << " | Adjacent: " << cell.getAdjacentMines()
                              << " | Revealed: " << (cell.isRevealed() ? "yes" : "no")
                              << " | Flagged: " << (cell.isFlagged() ? "yes" : "no")
                              << std::endl;

                    lastClickedX = x;
                    lastClickedY = y;
                    controller.onCellClicked(x, y);
                    update();
                });

                button->add_events(Gdk::BUTTON_PRESS_MASK);
                button->signal_button_press_event().connect([this, x, y](GdkEventButton* event) {
                    if (event->button == 3) { // Right-click
                        Cell& cell = controller.getGrid().getCell(x, y);
                        if (!cell.isRevealed()) {
                            cell.setFlagged(!cell.isFlagged());
                            std::cout << "Right-clicked (" << x << ", " << y << ") -> "
                                      << (cell.isFlagged() ? "Flagged" : "Unflagged") << std::endl;
                            update();
                        }
                        return true;
                    }
                    return false;
                });

                grid.attach(*button, x, y);
            }
        }
    }
    show_all_children();
}



void MainWindow::update() {

    int w = controller.getGrid().getWidth();
    int h = controller.getGrid().getHeight();

    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            auto button = dynamic_cast<CellButton*>(grid.get_child_at(x, y));
            if (!button) continue;

            const Cell& cell = controller.getGrid().getCell(x, y);
            if (cell.isRevealed()) {
                if (cell.isMine()) {
                    button->set_label("💣");
                }
				else {
                    int adj = cell.getAdjacentMines();
                    button->set_label(adj > 0 ? std::to_string(adj) : "0");
             	}
			} 
			else if (cell.isFlagged()) {
				button->set_label("🚩");
			}
            else {
                button->set_label("");
            }
        }
    }

    int cx = controller.getLastClickedX();
    int cy = controller.getLastClickedY();
    if (cx >= 0 && cy >= 0 && controller.getGrid().getCell(cx, cy).isMine()) {
        Gtk::MessageDialog dialog("You lost! 💥", false, Gtk::MESSAGE_ERROR);
        dialog.run();
        hide();
        return;
    }

    if (controller.getGrid().hasWon()) {
        Gtk::MessageDialog dialog("Congratulations! You've cleared the minefield!", false, Gtk::MESSAGE_INFO);
        dialog.run();
        hide();
    }
}

