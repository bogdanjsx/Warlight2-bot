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
    std::vector<Project, int> getAffordableProjects() const;

    // Comparator needed for the priority queue
    class Comparator 
    {
    public:
        bool operator() (const Project& p1, const Project& p2) const
        {
            return p1.getPriority() > p2.getPriority();
        }
    };

private:
    // All types of actions that can be done (conquer, attack, build defending walls, etc.)
    std::vector<Action*> actions;
    std::priority_queue<Project, std::vector<Project>, Comparator> projects;
    // Accepted projects along with the troops needed or / distributed by the Judge
    std::vector<std::pair<Project, int> > acceptedProjects;
    
    // TODO: Decide if a MapSearch object is needed inside Judge

};

#endif // JUDGE_H