#ifndef ACTION_H 
#define ACTION_H


/*
	This class represents an interface for the objects that will compute the way the bot acst on the
	map. After being inherited the obeject may create projects that will conquer efficiently a 
	superregion or may determine the way a "nail" (an infiltred troop) will act inside an enemy's 
	tertory. The only thing that concerns the programmer is the type of the object he's dealing with
	and the projects it produces. Obviously these objects are created based on strategy patterns so
	we can easely change a class that does something with a better class that does the same thing.
	This patterns helps us in the following way, we will be able of keeping trace of the development
	of a specific object and see the entire logic of an object at some point in time. 

	These classes will deal a lot with Mapsearch class for interogations.
*/

#include "Project.h"
#include <cstring>
#include <vector>



class Action 
{
public:
	/*
		Determine the name of the object in question.
		
		No parameter	
		return string with the name of the actual implementation of the object
		// may be changed with an enum afterwards
	*/
	virtual std::string getType() = 0;
	
	/*
		Computes, based on some models and queries, the way the bot make moves. 
		return a vector of projects which are in fact o bunch of movements but somehow linked 
		within a strategy of whatever the object is supposed to do.
	*/
	virtual std::vector<Project> getProjects() = 0; 
	Action() {}
	virtual ~Action() {}

};

#endif
