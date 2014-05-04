#include "menufactory.h"
#include "engine/game.h"

#include "gui/mainmenu.h"
#include "gui/pausemenu.h"
#include "gui/levelcompleted.h"
#include "gui/levelfailed.h"
#include "gui/levelchooser.h"

MenuFactory::MenuFactory(){}
MenuFactory::~MenuFactory(){}

Menu* MenuFactory::createMenu(MenuType menu, Game *parent) {
    switch(menu) {

    case BBMainMenu: {
        return new MainMenu(parent);
    }
    case BBLevelChooser: {
        return new LevelChooser(parent);
    }
    case BBPauseMenu: {
        return new PauseMenu(parent);
    }
    case BBLevelCompleted: {
        return new LevelCompleted(parent);
    }
    case BBLevelFailed: {
        return new LevelFailed(parent);
    }
    }
}

