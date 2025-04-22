#include <gtkmm/application.h>
#include "view/MainWindow.h"
#include "controller/GameController.h"

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.minesweeper");
    GameController controller(10, 10, 10);
    MainWindow window(&controller);
    return app->run(window);
}

