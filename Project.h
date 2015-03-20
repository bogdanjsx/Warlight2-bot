#ifndef PROJECT_H
#define PROJECT_H

// stl
#include <iostream>
#include <vector>
#include <iterator>

// project
#include "Bot.h"
#include "main.h"
#include "Parser.h"
#include "Region.h"
#include "SuperRegion.h"
#include "Movement.h"

class Project
{
public:
    Project();
    Project(const double& priority, const int& armies, const std::vector<Movement> movements);
    virtual ~Project();

    /**
     * Add a move to the whole project
     * @param move the specific Movement to add
     */
    void addMovement(const Movement& move);
    void delMovement(const unsigned int& index);

    void setMovements(const std::vector<Movement>& movements);
    void resetMovements();

    inline double getPriority() const { return priority; }
    inline int getArmiesNeeded() const { return armiesNeeded; }
    Movement getMovement(const size_t& index) const;
    std::vector<Movement> getMovements() const;

private:
    // total priority of the project
    double priority;
    // total amount of troops needed to achieve the project
    int armiesNeeded; 
    std::vector<Movement> movements;
};

#endif // PROJECT_H