#ifndef ABSTRACTCONQUER_H
#define ABSTRACTCONQUER_H

#include "Action.h"

/*
	This class will represent the interface for the objects that will deal with the conquer phase
	It will be instantiated with a fancy-algorithm object that will compute the best way the bot
	can develop and conquer a superregion.
*/

class AbstractConquer : public virtual Action {
public:
	// no parameters
	std::string getType() const { return type; }
	std::vector<int> getProjects();

protected:
	std::string type = "conquer";
};

#endif