#ifndef CONQUERER_H
#define CONQUERER_H

#include "AbstractConquer.h"

/*
	This class is contains the actual implementation for the way the bot will conquer a superregion.
*/

class Conquerer : public virtual AbstractConquer 
{
public:
	Conquerer();
	virtual ~Conquerer();
	// return a vector of projects 
	virtual std::vector<Project> getProjects();
};

#endif