#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "gui/menu.h"

class PauseMenu : public Menu
{
public:
    PauseMenu(Game *parent=0);
    ~PauseMenu();
};

#endif // PAUSEMENU_H
