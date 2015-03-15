// stl
#include <iostream>
#include <string>

//project
#include "Bot.h"

//tools
#include "tools/StringManipulation.h"
size_t	Bot::identificasuperregiuneobiectiv(){	// indicele superregiunii din care imi lipsesc cat mai putine, dar imi lipseste ceva
	size_t catam[100];	// cat detin din fiecare superregiune;
	size_t i,j,k;
	for ( i= 0; i<100; i++)
		catam[i] = 0;
	for (i = 0 ; i< ownedRegions.size(); ++i)
		catam[regions[i].getSuperRegion()]++;
	size_t aux = 100,ret =0;
	for ( i = 0 ; i< 100 ; i++)
		if( ( superRegions[i].size() > catam[i] ) && ( aux > (superRegions[i].size() - catam[i])) ){
			aux = superRegions[i].size() - catam[i];
			ret = i;
		}
	return ret;
}
void Bot::creazaproiecte(int pass){	
	// pass = 0 pentru a ataca superregiune_obiectiv
	// pass = 1 pentru a ataca orice.
	size_t i,j,rc,nc;
	int placenr, movenr;
	size_t superregiune_obiectiv;
	if(pass == 1)
		superregiune_obiectiv = Bot::identificasuperregiuneobiectiv();
	for ( i = 0 ; i < ownedRegions.size(); ++i){
		rc = ownedRegions[i];	// regiunea curenta;
		for( j = 0; j < regions[rc].getNbNeighbors(); ++j){
			nc = regions[rc].getNeighbor(j);
			if(regions[nc].getOwner() != ME && 
					( (regions[nc].getSuperRegion() == superregiune_obiectiv)
					  || (pass == 1)
					  )
					)
				if(regions[nc].getArmies() * 14 < (regions[rc].getArmies() - 1 + armiesLeft) * 10){
					movenr = regions[nc].getArmies()*14/10 + 1;
					placenr = movenr +1 - regions[rc].getArmies();
					(placenr < 0)?0:placenr;
					proiecte.push_back( proiect(rc, placenr, rc, nc, movenr, 3) );
					regions[rc].setArmies( (movenr>=regions[rc].getArmies())? 1: (regions[rc].getArmies()-movenr) );
					// a modificat regions.Armies ca sa nu se bazeze pe armatele respective in urmatoarele mutari!
					armiesLeft -= placenr;
					// a modificat si armiesLeft ca su nu mai faca proiecte. Va trebui schimbat asta in momentul in care sunt folosite prioritatile.
				}
		}
	}
}
Bot::Bot() :
		armiesLeft(0), timebank(0), timePerMove(0), maxRounds(0), parser(this), phase(NONE)
{
}

Bot::~Bot()
{

}

void Bot::playGame()
{
	parser.parseInput();
}

void Bot::pickStartingRegion()
{
	// START HERE!
	std::cout << startingRegionsreceived.front() << std::endl;
}

void Bot::placeArmies()
{
	for( size_t i = 0 ; i <proiecte.size(); ++i)
		if(proiecte[i].placenr){
			std::cout << botName << " place_armies " << proiecte[i].placein << " " << proiecte[i].placenr;
		}
	// START HERE!
	if(armiesLeft >0){
		unsigned region = std::rand() % ownedRegions.size();
		std::cout << botName << " place_armies " << ownedRegions[region] << " " << armiesLeft;
	}
	std::cout << std::endl;
	addArmies(ownedRegions[region], armiesLeft);
}

void Bot::makeMoves()
{
	// START HERE!
	/// Output No moves when you have no time left or do not want to commit any moves.
	// std::cout << "No moves "  << std::endl;
	/// Anatomy of a single move
	//  std::cout << botName << " attack/transfer " << from << " " << to << " "<< armiesMoved;
	/// When outputting multiple moves they must be seperated by a comma
	std::vector<std::string> moves;
	for (size_t i = 0; i < proiecte.size(); ++i)
		if(proiecte[i].movenr){
			std::stringstream move;
			// obs: eregions.Armies a fost modificat si nu mai este relevant !!
			move << botName << " attack/transfer " << proiecte[i].movefrom << " " << proiecte[i].moveto << " " << proiecte[i].movenr;
			moves.push_back(move.str());
		}
	proiecte.clear();
/*
	for (size_t j = 0; j < ownedRegions.size(); ++j)
	{
		std::stringstream move;
		int i = ownedRegions[j];
		if (regions[i].getArmies() <= 1)
			continue;

		int target = regions[i].getNeighbor(std::rand() % regions[i].getNbNeighbors());
		// prefer enemy regions
		for ( unsigned k = 0; k < 5; ++k)
		{
			if(regions[target].getOwner() != ME) break;
			target = regions[i].getNeighbor(std::rand() % regions[i].getNbNeighbors());
		}
		move << botName << " attack/transfer " << i << " "
				<< target << " "
				<< (regions[i].getArmies() - 1);
		moves.push_back(move.str());
	}
*/
	std::cout << string::join(moves) << std::endl;
}

void Bot::addRegion(const unsigned& noRegion, const unsigned& noSuperRegion)
{
	while (regions.size() <= noRegion)
	{
		regions.push_back(Region());
	}
	regions[noRegion] = Region(noRegion, noSuperRegion);
	superRegions[noSuperRegion].addRegion(noRegion);
}
void Bot::addNeighbors(const unsigned& noRegion, const unsigned& neighbors)
{
	regions[noRegion].addNeighbor(neighbors);
	regions[neighbors].addNeighbor(noRegion);
}
void Bot::addWasteland(const unsigned &noRegion)
{
	wastelands.push_back(noRegion);
}
void Bot::addSuperRegion(const unsigned& noSuperRegion, const int&reward)
{
	while (superRegions.size() <= noSuperRegion)
	{
		superRegions.push_back(SuperRegion());
	}
	superRegions[noSuperRegion] = SuperRegion(reward);
}

void Bot::setBotName(const std::string& name)
{
	botName = name;
}
void Bot::setOpponentBotName(const std::string& name)
{
	opponentBotName = name;
}
void Bot::setArmiesLeft(const int& nbArmies)
{
	armiesLeft = nbArmies;
}
void Bot::setTimebank(const int &newTimebank)
{
	timebank = newTimebank;
}
void Bot::setTimePerMove(const int &newTimePerMove)
{
	timePerMove = newTimePerMove;
}
void Bot::setMaxRounds(const int &newMaxRounds)
{
	maxRounds = newMaxRounds;
}

void Bot::clearStartingRegions()
{
	startingRegionsreceived.clear();
}

void Bot::addStartingRegion(const unsigned& noRegion)
{
	startingRegionsreceived.push_back(noRegion);
}

void Bot::addOpponentStartingRegion(const unsigned& noRegion)
{
	opponentStartingRegions.push_back(noRegion);
}
void Bot::opponentPlacement(const unsigned & noRegion, const int & nbArmies)
{
	// suppress unused variable warnings
	(void) noRegion;
	(void) nbArmies;

	// TODO: STUB
}
void Bot::opponentMovement(const unsigned &noRegion, const unsigned &toRegion, const int &nbArmies)
{
	// suppress unused variable warnings
	(void) noRegion;
	(void) toRegion;
	(void) nbArmies;

	// TODO: STUB
}

void Bot::startDelay(const int& delay)
{
	// suppress unused variable warnings
	(void) delay;
	// TODO: STUB
}
void Bot::setPhase(const Bot::Phase pPhase)
{
	phase = pPhase;
}
void Bot::executeAction()
{
	if (phase == NONE)
		return;
	if (phase == Bot::PICK_STARTING_REGION)
	{
		pickStartingRegion();
	}
	else if (phase == Bot::PLACE_ARMIES)
	{
		placeArmies();
	}
	else if (phase == Bot::ATTACK_TRANSFER)
	{
		makeMoves();
	}
	phase = NONE;
}

void Bot::updateRegion(const unsigned& noRegion, const  std::string& playerName, const int& nbArmies)
{
	Player owner;
	if (playerName == botName)
		owner = ME;
	else if (playerName == opponentBotName)
		owner = ENEMY;
	else
		owner = NEUTRAL;
	regions[noRegion].setArmies(nbArmies);
	regions[noRegion].setOwner(owner);
	if (owner == ME)
		ownedRegions.push_back(noRegion);
}
void Bot::addArmies(const unsigned& noRegion, const int& nbArmies)
{
	regions[noRegion].setArmies(regions[noRegion].getArmies() + nbArmies);
}
void Bot::moveArmies(const unsigned& noRegion, const unsigned& toRegion, const int& nbArmies)
{
	if (regions[noRegion].getOwner() == regions[toRegion].getOwner() && regions[noRegion].getArmies() > nbArmies)
	{
		regions[noRegion].setArmies(regions[noRegion].getArmies() - nbArmies);
		regions[toRegion].setArmies(regions[toRegion].getArmies() + nbArmies);
	}
	else if (regions[noRegion].getArmies() > nbArmies)
	{
		regions[noRegion].setArmies(regions[noRegion].getArmies() - nbArmies);
		if (regions[toRegion].getArmies() - std::round(nbArmies * 0.6) <= 0)
		{
			regions[toRegion].setArmies(nbArmies - std::round(regions[toRegion].getArmies() * 0.7));
			regions[toRegion].setOwner(regions[noRegion].getOwner());
		}
		else
		{
			regions[noRegion].setArmies(
					regions[noRegion].getArmies() + nbArmies - std::round(regions[toRegion].getArmies() * 0.7));
			regions[toRegion].setArmies(regions[toRegion].getArmies() - std::round(nbArmies * 0.6));
		}
	}
}

void Bot::resetRegionsOwned()
{
	ownedRegions.clear();
}
