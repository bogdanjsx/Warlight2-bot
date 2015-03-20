// project
#include "Project.h"

Project::Project()
    : priority(0)
    , armiesNeeded(0)
{
}

Project::Project(const double& priority, const int& armies, const std::vector<Movement> movements)
    : priority(priority)
    , armiesNeeded(armies)
    , movements(movements)
{
}

Project::~Project()
{
}

void Project::addMovement(const Movement& move)
{
    priority += move.getPriority();
    armiesNeeded += move.getArmiesNeeded();
    movements.push_back(move);
}

void Project::delMovement(const unsigned int& index)
{
    if (index < movements.size())
        movements.erase(movements.begin() + index);
}

void Project::setMovements(const std::vector<Movement>& movements)
{
    this->movements = movements;
}

void Project::resetMovements()
{
    movements.clear();
}

Movement Project::getMovement(const size_t& index) const
{
    return movements.at(index);
}

std::vector<Movement> Project::getMovements() const
{
    return movements;
}