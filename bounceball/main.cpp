#include "bounceball.h"
#include <QApplication>
#include <iostream> // slett

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Bounceball b(1024,768);
    b.run();
    QDir dir(QCoreApplication::applicationDirPath());
    #if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" ||
        dir.dirName().toLower() == "release")
    {
        dir.cdUp();
    }
    #elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
    #endif
    /*if(dir.exists())
        QDir::setCurrent(dir.absolutePath());*/

    std::cout << dir.QDir::currentPath().toStdString() << std::endl;

    return a.exec();
}
