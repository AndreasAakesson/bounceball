#ifndef BRICKFACTORY_H
#define BRICKFACTORY_H

#include "entites/brick.h"

class BrickFactory
{
public:
    enum FactoryType {
        DefaultBrickFactory // only one atm
    };

    BrickFactory(FactoryType factory_type = DefaultBrickFactory);
    Brick* createBrick(int healthpoints);
private:
    FactoryType factory;

};

#endif // BRICKFACTORY_H
