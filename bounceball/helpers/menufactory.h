#ifndef MENUFACTORY_H
#define MENUFACTORY_H

#include "gui/menu.h"

class Game;

class MenuFactory
{
    MenuFactory();
    ~MenuFactory();
public:
    enum MenuType {
        BBMainMenu,
        BBLevelChooser,
        BBPauseMenu,
        BBLevelCompleted,
        BBLevelFailed
    };

    static Menu* createMenu(MenuType menu, Game *parent);
};

#endif // MENUFACTORY_H
