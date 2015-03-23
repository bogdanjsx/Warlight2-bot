#ifndef ABSTRACTATTACK_H
#define ABSTRACTATTACK_H


#include "Action.h"

/*
	This class will represent the interface for the objects that will deal with the conquer phase
	It will be instantiated with a fancy-algorithm object that will compute the best way the bot
	can attack the enemy.
*/

class AbstractAttack : public virtual Action 
{
public:
	// no parameters
	virtual std::string getType() const { return type; }

protected:
	std::string type = "attack";
};

#endif