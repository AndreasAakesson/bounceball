#ifndef GAME_H
#define GAME_H

#include <QGraphicsView> // inherited
#include <QVector> // to store levels
#include "helpers/levelfactory.h" // level & factory
#include "gui/button.h"

class Menu;

class Game : public QGraphicsView
{
    LevelFactory levelFactory; // level factory (there is only 1 atm).
    Level* currentLevel; // current level
    QVector<QString> levellist; // list of all avaliable levels
    QMap<QString, Menu*> menus; // all avaliable menus
public:
    Game(int width, int height, QWidget* parent = 0);
    const static int FPS;

    enum State {
        Uninitiliazed,
        ShowingMenu,
        Playing,
        Paused
    };
    static int Width;
    static int Height;

    void init(); // setup game
    void start(); // start level
    void pause(); // pause level
    void resetLevel(); // reset ball(s)
    void restartLevel(); // replay the current level
    void exitLevel();
    void exitGame();
    void showMenu(QString menu_key);
    void levelEnded(Level::EndState endstate);
    Level& level(); // return the current level
    QVector<QString>& levelList(); // return list of all levels

    ~Game();
private:
    State g_state; // current state of game (used less than original thought..)
    QVector<QString> getLevels(const QDir &levelpath); // get all levels in given directory

    void setCurrentLevel(Level* level); // change level
    void handleButtonClick(Button &button);

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // GAME_H
