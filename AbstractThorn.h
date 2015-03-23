#ifndef ABSTRACTTHORN_H
#define ABSTRACTTHORN_H

#include "Action.h"

/*
	This class will represent the interface for the objects that will deal with the undermine phase
	It will be instantiated with a fancy-algorithm object that will compute the best way the bot
	can undermine the enemy.
*/

class AbstractThorn : public virtual Action 
{
public:
	// no parameters
	virtual std::string getType() const { return type; }
protected:
	std::string type = "thorn";
};

#endif