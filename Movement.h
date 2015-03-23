#ifndef MOVEMENT_H
#define MOVEMENT_H

// stl
#include <utility>
#include <iostream>

class Movement
{
public:
    Movement();
    /**
     * Constructor used when moving from one region to another is wanted
     */
    Movement(const double& priority, const int& moveFrom, const int& moveTo, const int& armiesNeeded);
    /**
     * Constructor used when the intention is to only place part of the income troops
     * on a specific region that you already own
     */
    Movement(const double& priority, const int& placeIn, const int& armiesNeeded);
    virtual ~Movement();

    void setPriority(const double& priority) { this->priority = priority; }
    /**
     * Set source and destination for a next army movement on the map
     * @param sourceRegion id of the starting region
     * @param destinationRegion id of the target region
     */
    void setTarget(const int& sourceRegion, const int& destinationRegion);
    /**
     * Set region to place income troops on it
     * @param region id of the target region
     */
    void setPlaceInRegion(const int& region) { this->placeIn = region; }
    /**
     * Set the number of troops needed to achieve the current movement
     */
    void setArmiesNeeded(const int& armies) { this->armiesNeeded = armies; }

    inline double getPriority() const { return priority; }
    inline int getArmiesNeeded() const { return armiesNeeded; }
    inline int getPlaceInRegion() const { return placeIn; }
    inline std::pair<int, int> getMoveCoordinates() const;

private:
    double priority;
    int moveFrom;
    int moveTo;
    int placeIn;
    int armiesNeeded;
};

#endif // MOVEMENT_H