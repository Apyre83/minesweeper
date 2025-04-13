#ifndef __CELLBUTTON_H
#define __CELLBUTTON_H

#include <gtkmm/button.h>

class CellButton : public Gtk::Button {
public:
    CellButton(int x, int y);

    int getX() const;
    int getY() const;

private:
    int x, y;
};


#endif /* __CELLBUTTON_H */
