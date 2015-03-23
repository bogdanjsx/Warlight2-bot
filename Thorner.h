#ifndef THORNER_H
#define THORNER_H

#include "AbstractThorn.h"

/*
	This class is contains the actual implementation for the way the bot will assure that
	enemy does'nt get bonus on some critical regions.
*/


class Thorner : public virtual AbstractThorn {
public:
	Thorner();
	virtual ~Thorner();
	// return a vector of projects 
	virtual std::vector<Project> getProjects();
};


#endif