// project
#include "Movement.h"

Movement::Movement()
    : priority(0)
    , moveFrom(0)
    , moveTo(0)
    , placeIn(0)
    , armiesNeeded(0)
{
}

Movement::Movement(const int& priority, const int& moveFrom, const int& moveTo, const int& armiesNeeded)
    : priority(priority)
    , moveFrom(moveFrom)
    , moveTo(moveTo)
    , placeIn(0)
    , armiesNeeded(armiesNeeded)
{
}

Movement::Movement(const int& priority, const int& placeIn, const int& armiesNeeded)
    : priority(priority)
    , moveFrom(0)
    , moveTo(0)
    , placeIn(placeIn)
    , armiesNeeded(armiesNeeded)
{
}

Movement::~Movement()
{
}

void Movement::setTarget(const int& sourceRegion, const int& destinationRegion)
{
    moveFrom = sourceRegion;
    moveTo = destinationRegion;
}

inline std::pair<int, int> Movement::getMoveCoordinates() const
{
    return std::make_pair(moveFrom, moveTo);
}
