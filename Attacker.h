#ifndef ATTACKER_H
#define ATTACKER_H

#include "AbstractAttack.h"

/*
	This class is contains the actual implementation for the way the bot will attack the enemy.
*/


class Attacker : public virtual AbstractAttack 
{
public:
	Attacker();
	virtual ~Attacker();
	// return a vector of projects 
	virtual std::vector<Project> getProjects();
};


#endif