#ifndef LEVELFILE_H
#define LEVELFILE_H

#include <QFile>
#include <QString>
#include <QGenericMatrix>

typedef int Column;
typedef QVector<Column> Row;
typedef QVector<Row> Map;
class LevelFile
{
    QFile* level;
    Map map;
public:
    LevelFile(QString level);
    ~LevelFile();

    int operator()(int row, int col);

    QString toQString();
    bool isValid(int rows, int cols);
};

#endif // LEVELFILE_H
