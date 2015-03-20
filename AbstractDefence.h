#ifndef ABSTRACTDEFENCE_H
#define ABSTRACTDEFENCE_H

#include <vector>
#include <cstring>
#include "Action.h"

/*
	This class will represent the interface for the objects that will deal with the conquer phase
	It will be instantiated with a fancy-algorithm object that will compute the best way the bot
	can deffend against the enemmy.
*/

class AbstractDefence : public virtual Action {
public:
	// no parameters
	std::string getType() const { return type; }
	std::vector<Project> getProjects();
protected:
	std::string type = "defence";
};

#endif