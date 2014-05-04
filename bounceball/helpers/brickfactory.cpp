#include "brickfactory.h"

BrickFactory::BrickFactory(FactoryType factory_type)
{
    factory = factory_type;
}

Brick* BrickFactory::createBrick(int healthpoints) {

    Q_ASSERT(factory);

    switch(factory) {

    case DefaultBrickFactory: {
        return new Brick(healthpoints);
    }

    default: {
        return new Brick(healthpoints);
    }
    }
}
