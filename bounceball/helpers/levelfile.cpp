#include "levelfile.h"

#include <stdexcept>
#include <iostream> // slett

using namespace std;

LevelFile::LevelFile(QString file)
{
    // open file
    level = new QFile(file);
    if(!level->open(QIODevice::ReadOnly)) {
        throw runtime_error("Couldn't open file");
    }

    // create stream
    QTextStream in(level);
    in.setIntegerBase(10);

    // read through file, put into map
    QChar l;
    int row = 0;
    map.append(Row());
    while(!in.atEnd()) {
        in >> l; // read each letter
        if(l == QChar::Space) // ignore space
            continue;
        else if(l == QChar::LineFeed) { // new row
            map.append(Row());
            row++;
        }
        else if(l.isNumber()) { // add number to map
            map[row].append(l.digitValue());
        }
    }

    level->close();
}

LevelFile::~LevelFile() {
    level->close();
}

int LevelFile::operator()(int row, int col) {
    return map[row][col];
}

QString LevelFile::toQString() {
    QString output;

    for(int i = 0; i < map.size(); i++) {
        Row row = map[i];
        for(int j = 0; j < row.size(); j++) {
            output.append(QString::number(row[j])).append(" ");
        }
        output.append("\n");
    }
    return output;
}

bool LevelFile::isValid(int rows, int cols) {
    // correct amount of rows?
    if(map.size() != rows)
        return false;
    // correct amount of cols?
    for(int i = 0; i < map.size(); i++) {
        if(map[i].size() != cols)
            return false;
    }
    return true;
}
