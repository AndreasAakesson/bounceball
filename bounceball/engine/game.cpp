#include "game.h"

#include <QDir>

#include <iostream> // slett
#include <stdexcept>
#include "helpers/menufactory.h"
#include <QApplication>

using namespace std;

const int Game::FPS = 25;
int Game::Width = 1024;
int Game::Height = 768;

Game::Game(int width, int height, QWidget* parent) :
    QGraphicsView(parent)
{
    // make width and height public
    Width = width;
    Height = height;
    // sets default level factory
    levelFactory = LevelFactory(this);
    // no active level
    currentLevel = 0;
    // game state: Uninitiliazed
    g_state = Uninitiliazed;

    // enables mouse tracking.
    setMouseTracking(true);

    // view settings
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    resize(width, height);
}

void Game::init() {
    // setup/init game

    // read levels
    levellist = getLevels(Level::LevelPath);

    // show main menu
    menus.insert("main", MenuFactory::createMenu(MenuFactory::BBMainMenu, this));
    showMenu("main");

    show();
}

void Game::start() {
    // throw exception if game hasn't been initialized
    if(g_state == Uninitiliazed)
        throw runtime_error("Cannot start unitialized game!");

    // if no level, pick first
    if(!currentLevel) {
        throw runtime_error("Trying to start a level when none is created, exiting..");
        //Level* level = levelFactory.createLevel(levellist[0]);
        //setCurrentLevel(level);
    }
    // if there isnt already a pause menu
    if(!menus.contains("pause"))
        menus.insert("pause", MenuFactory::createMenu(MenuFactory::BBPauseMenu, this));

    setScene(currentLevel);
    currentLevel->pause();
    g_state = Playing;
    setCursor(Qt::BlankCursor);
}

void Game::pause() {
    currentLevel->pause();
    showMenu("pause");
}

void Game::resetLevel() {
    currentLevel->removeGameObject(Ball::Type);
    levelFactory.createBall(currentLevel);
}

void Game::restartLevel() {
    cout << "Implement if time..." << endl;
}

void Game::exitLevel() {
    showMenu("main");
    delete currentLevel;
    currentLevel = 0;
}

void Game::exitGame() {
    // do necessary writing, if needed..
    QApplication::instance()->quit();
}

void Game::showMenu(QString menu_key) {
    if(!menus.contains(menu_key))
        throw runtime_error("Trying to show a menu that doesn't exsist, exiting...");

    g_state = ShowingMenu;
    setScene(menus[menu_key]);
    unsetCursor();
}

void Game::levelEnded(Level::EndState endstate) {
    currentLevel->pause();
    QString menu_key("levelended");
    Menu* endmenu;

    // remove end menu if it already exsists, one will always be active in heap..
    if((endmenu = menus[menu_key])) {
        menus.remove(menu_key);
        delete endmenu;
    }

    if(endstate == Level::Completed) {
        endmenu = MenuFactory::createMenu(MenuFactory::BBLevelCompleted, this);
    }
    else {
        endmenu = MenuFactory::createMenu(MenuFactory::BBLevelFailed, this);
    }
    menus.insert(menu_key, endmenu);
    showMenu(menu_key);
}

Level& Game::level() {
    return *currentLevel;
}

QVector<QString>& Game::levelList() {
    // update list once more to make sure no new levels are made or deleted in runtime (would be weird if there was..)
    levellist = getLevels(Level::LevelPath);

    return levellist;
}

QVector<QString> Game::getLevels(const QDir &levelpath) {
    // get all entries
    QStringList list = levelpath.entryList(QDir::Files);

    QVector<QString> levels;
    foreach(QString str, list) {
        levels.append(str);
        std::cout << str.toStdString() << std::endl;
    }
    return levels;
}

void Game::setCurrentLevel(Level *level) {
    if(currentLevel)
        delete currentLevel;
    currentLevel = level;
}

void Game::mousePressEvent(QMouseEvent *event) {
    // block mouse press while game is not in menu state
    if(g_state != ShowingMenu)
        return;

    // see if any item is clicked
    if(QGraphicsItem* item = scene()->itemAt(event->pos(), QTransform())) {
        // only buttons will be handled
        if(Button* button = qgraphicsitem_cast<Button*>(item)) {
            handleButtonClick(*button);
        }
    }
}

void Game::handleButtonClick(Button &button) {
    button.playSound();
    switch(button.gameFunction()) {

    case Button::GFunctionQuickStart: { // Play first level (or random?)
        setCurrentLevel(levelFactory.createLevel(levellist[0]));
        start();
        break;
    }

    case Button::GFunctionMainMenu: { // Show main menu
        showMenu("main");
        break;
    }

    case Button::GFunctionLevelChooser: { // Go to level chooser
        if(!menus.contains("levelchooser"))
            menus.insert("levelchooser", MenuFactory::createMenu(MenuFactory::BBLevelChooser, this));
        showMenu("levelchooser");
        break;
    }

    case Button::GFunctionPlayLevel: { // Play level given buttons level_key;
        int key = button.levelKey();
        if(key < 0 || key >= levellist.size())
            throw runtime_error("Button points to a level in levellist that doesnt exsists, exiting..");

        QString levelname = levellist[key];
        Level* level = levelFactory.createLevel(levelname);
        setCurrentLevel(level);
        start();
        break;
    }

    case Button::GFunctionTestLevel: { // Start test level
        setCurrentLevel(levelFactory.createTestLevel());
        start();
        break;
    }

    case Button::GFunctionResumeLevel: { // Resume current level
        start();
        break;
    }

    case Button::GFunctionRestartLevel: { // Restart current level
        restartLevel();
        break;
    }

    case Button::GFunctionExitLevel: { // Exit current level
        exitLevel();
        break;
    }

    case Button::GFunctionExitGame: {
        exitGame();
        break;
    }

    case Button::GFunctionNone: {
        cout << "Not yet implemented.." << endl;
        break;
    }
    } // end of switch(button)
}

void Game::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Escape: {
        if(scene() == currentLevel && currentLevel->isRunning())
            pause();
        else if(scene() == menus["pause"] && !currentLevel->isRunning())
            start();
        break;
    }
    case Qt::Key_Space: {
        if(scene() == currentLevel && !currentLevel->isRunning())
            currentLevel->start();
        break;
    }
    }
}

Game::~Game() {
    delete currentLevel;
    foreach(QGraphicsScene* menu, menus) {
        delete menu;
    }
}
