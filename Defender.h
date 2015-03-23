#ifndef DEFENDER_H
#define DEFENDER_H

#include "AbstractDefence.h"

/*
	This class is contains the actual implementation for the way the bot will defend.
*/


class Defender : public virtual AbstractDefence {
public:
	Defender();
	virtual ~Defender();
	// return a vector of projects 
	virtual std::vector<Project> getProjects();
};


#endif