#include "menu.h"

#include <iostream>

#ifdef Q_OS_MACX
const QDir Menu::soundDir = QDir("../Resources/audio/gui");
#else
const QDir Menu::soundDir = QDir("./audio/gui");
#endif


Menu::Menu(Game *parent) :
    QGraphicsScene(parent)
{
    Q_INIT_RESOURCE(gui);
    QPixmap logo;
    logo_height = 0;
    if(logo.load(":/img/logo.png")) {
        QGraphicsPixmapItem* item = addPixmap(logo);
        item->setPos(sceneRect().width() - item->boundingRect().width()/4,10);
        logo_height = item->boundingRect().height()+10;
    }

    offset_top = logo_height;

    Q_CLEANUP_RESOURCE(gui);
}

void Menu::addButtons(QVector<Button*> &b_vector) {
    for(int i = 0; i < b_vector.size(); i++) {
        Button* b = b_vector[i];
        addItem(b);

        // center button on scene
        b->setPos(m_width - b_width/2, b_margin + i*(b_margin+b_height)+offset_top);
    }
}

Menu::~Menu() {
    clear();
}
