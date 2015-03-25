#include "Conquerer.h"


/*
	Here is the code that actually does something.
	
	Conquerer 1.0 => "First Approach"

	Base ideas:
		1. If we can conquer a superregion then we will demand with a high priority to do that.
		2. If we can't do that, then we calculate what moves will assure the fastest conquer of that
			superregion.
		3. We take in acount that with a propability after conquering a region there will remain
			a junk amount of armies which we will reuse probably for another move next round
		4. We will do this moves in a way that we will not leave the junk at some point impractical
			or useless to reuse(e.g after qonquering an island in "waves" at the final at the "end"
			of the island will be some armies that will be very far from a sensible point). We will
			keep an eye on that too.
*/

Conquerer::Conquerer()
{
}

Conquerer::~Conquerer()
{
}

std::vector<Project> Conquerer::getProjects() 
{
	std::vector<Project> projects;
	// TODO : implement

	return projects;
}
