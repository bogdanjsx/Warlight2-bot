// project
#include "Judge.h"
#include "Attacker.h"
#include "Conquerer.h"
#include "Defender.h"
#include "Thorner.h"

#include <vector>
#include <algorithm>

Judge::Judge()
{
    // Create all types of possible actions
    actions.push_back(new Conquerer());
    actions.push_back(new Defender());
    actions.push_back(new Attacker());
    actions.push_back(new Thorner());
}

Judge::~Judge()
{
    for (auto i = 0u; i < actions.size(); i++)
        delete actions[i];
}

void Judge::collectProjects()
{   
    // Make last state forgotten
    projects.clear();
    acceptedProjects.clear();

    for (auto &action : actions) {
        std::vector<Project> vp = action->getProjects();

        for (auto &project : vp) {
            projects.push_back(project);
        }
    }

    std::sort(projects.begin(), projects.end(), ProjectComparator());
}

/**
 * Apply a Greedy strategy to determine which projects we should accept 
 * for deployment and which ones we shouldn't.
 */
void Judge::calculateProjectsDistribution()
{
    auto p = 0u;
    // Still can accept a whole project
    while (availableArmies - projects[p].getArmiesNeeded() >= 0) {
        acceptedProjects.push_back(projects[p]);
        // Update current state
        availableArmies -= projects[p].getArmiesNeeded();
        p++;
    }

    // Create a new project with the most profitable movements from the last project unsupported
    std::vector<Movement> movements = projects[p].getMovements();
    std::sort(movements.begin(), movements.end(), MovementComparator());

    Project lastProjectAccepted;

    auto m = 0u;
    while (availableArmies - movements[m].getArmiesNeeded() >= 0) {
        lastProjectAccepted.addMovement(movements[m]);
        availableArmies -= movements[m].getArmiesNeeded();
        m++;
    }

    // If a last project can be supported
    if (lastProjectAccepted.getArmiesNeeded() > 0)
        acceptedProjects.push_back(lastProjectAccepted);
}

void Judge::setAvailableArmies(int armiesNb)
{
    availableArmies = armiesNb;
}