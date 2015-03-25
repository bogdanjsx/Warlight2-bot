#ifndef JUDGE_H
#define JUDGE_H

// stl
#include <vector>
#include <queue>

// project
#include "Action.h"
#include "Project.h"

class Judge 
{
public:
    Judge();
    // TODO: Judge constructor with some parameters
    virtual ~Judge();

    /**
     * Query each and every item of the Actions vector, get the projects
     * and insert them in the priority_queue
     */
    void collectProjects();
    /**
     * Based on each project priority and also on how much resources (aka. troops)
     * we have available to make moves at one time, calculate which projects are affordable
     * to accomplish
     * The result is stored in a vector of pairs.
     */
    void calculateProjectsDistribution();
    /**
     * @return: accepted projects for accomplishment
     */
    std::vector<Project> getAffordableProjects() const { return acceptedProjects; }

    // Armies available for deployment in the current round
    void setAvailableArmies(int armiesNb);

    // Comparator needed for the priority queue
    class ProjectComparator
    {
    public:
        bool operator() (const Project& p1, const Project& p2) const
        {
            return (p1.getPriority() / p1.getArmiesNeeded()) > (p2.getPriority() / p1.getArmiesNeeded());
        }
    };

    class MovementComparator
    {
    public:
        bool operator() (const Movement& m1, const Movement& m2) const
        {
            return (m1.getPriority() / m1.getArmiesNeeded()) > (m2.getPriority() / m2.getArmiesNeeded());
        }
    };

    // TODO: Add methods for reseting the queue and the acceptedProjects vector

private:
    // All types of actions that can be done (conquer, attack, build defending walls, etc.)
    std::vector<Action*> actions;
    // It's better to use a vector then sort it one time, instead of a p_queue
    std::vector<Project> projects;
    // Accepted projects by the Judge
    std::vector<Project> acceptedProjects;
    int availableArmies;
    
    // TODO: Decide if a MapSearch object is needed inside Judge

};

#endif // JUDGE_H