#include "mainmenu.h"

#include <iostream> // slett

MainMenu::MainMenu(Game* parent) :
    Menu(parent)
{
    // set size
    setSceneRect(parent->rect());
    m_width = sceneRect().width()/2;
    setBackgroundBrush(Qt::gray);

    // sets button attributes
    b_margin = 20;
    b_width = m_width - b_margin*2;
    b_height = 100;

    // buttons for main menu
    buttons.append(new Button(b_width, b_height, "Quick Start", Button::GFunctionQuickStart));
    buttons.append(new Button(b_width, b_height, "Choose Level..", Button::GFunctionLevelChooser));
    buttons.append(new Button(b_width, b_height, "Play Test Level", Button::GFunctionTestLevel));
    buttons.append(new Button(b_width, b_height, "Exit Game", Button::GFunctionExitGame));

    addButtons(buttons);
}

MainMenu::~MainMenu() {

}
