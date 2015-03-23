// stl
#include <iostream>
#include <string>

//project
#include "Bot.h"

//tools
#include "tools/StringManipulation.h"
size_t Bot::identificasuperregiuneobiectiv() {	// indicele superregiunii din care imi lipsesc cat mai putine, dar imi lipseste ceva
	size_t catam[50];	// cat detin din fiecare superregiune;
	size_t i, j, k;
	for (i = 0; i < 50; ++i)
		catam[i] = 0;
	for (i = 0; i < ownedRegions.size(); ++i)
		catam[regions[i].getSuperRegion()]++;
	size_t aux = 100,ret = 300;
	for ( i = 0 ; i < 50 ; i++)
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
	int ncsalvat = 0;
	size_t superregiune_obiectiv;
	if(pass == 0)
		superregiune_obiectiv = Bot::identificasuperregiuneobiectiv();
	if((superregiune_obiectiv == 300) && (pass == 0))
		return;
	for (i = 0 ; i < ownedRegions.size(); ++i)
	{
		rc = ownedRegions[i];	// regiunea curenta;
		for( j = 0; j < regions[rc].getNbNeighbors(); ++j){
			nc = regions[rc].getNeighbor(j);
			if( (regions[nc].getOwner() != ME) && 
					( (regions[nc].getSuperRegion() == superregiune_obiectiv)
					  || (pass == 1)
					  )
					)
				if(nrarmate[nc] * 14 < (nrarmate[rc] - 1 + armiesLeft) * 10){
					movenr = nrarmate[nc]*14/10 + 1;
					placenr = movenr +1 - nrarmate[rc];
					while(placenr > armiesLeft)
						placenr--;
					if( nrarmate[rc] > 30 ) {
						placenr = armiesLeft;
						movenr = placenr + nrarmate[rc] -1;
					}
					(placenr < 0) ? 0 : placenr;
					proiecte.push_back(proiect(rc, placenr, rc, nc, movenr, 3));
					nrarmate[rc] -= movenr - 1 - placenr; 
					// a modificat regions.Armies ca sa nu se bazeze pe armatele respective in urmatoarele mutari!
					armiesLeft -= placenr;
					// a modificat si armiesLeft ca su nu mai faca proiecte. Va trebui schimbat asta in momentul in care sunt folosite prioritatile.
					if(movenr)
						ammutari = 1;
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
	std::cout << startingRegionsreceived.front() << std::endl;
}

void Bot::placeArmies()
{
	size_t i, j;
	proiecte.clear();
	for( i = 0; i < regions.size(); ++i)
		nrarmate[i] = regions[i].getArmies();
	ammutari = 0;
	creazaproiecte(0);
	creazaproiecte(1);
	int pus1 = 0;
	if(proiecte.size() > 0 && proiecte.size() < 20)
	for( i = 0 ; i <proiecte.size(); ++i)
		if(proiecte[i].placenr > 0 && proiecte[i].placein > 0 && regions[proiecte[i].placein].getOwner() == ME){
			if(pus1)
				std::cout << ",";
			else
				pus1 = 1;
			std::cout << botName << " place_armies " << proiecte[i].placein << " " << proiecte[i].placenr;
		}

	if(armiesLeft > 0){
		for( i = 0; i< ownedRegions.size(); ++i)
			for (j = 0; j< regions[ownedRegions[i]].getNbNeighbors(); ++j)
				if( (regions[regions[ownedRegions[i]].getNeighbor(j)].getOwner() == ENEMY) && armiesLeft ){
					if(pus1)
						std::cout << ",";
					else
						pus1 = 1;
					std::cout << botName << " place_armies " << ownedRegions[i] << " " << armiesLeft;
					armiesLeft = 0;
					i = ownedRegions.size();
					break;
				}
	}
	unsigned region;
	if(armiesLeft > 0){
		if(pus1)
			std::cout << ",";
		else
			pus1 = 1;
		region = ownedRegions[1]; //std::rand() % ownedRegions.size();
		std::cout << botName << " place_armies " << ownedRegions[region] << " " << armiesLeft;
	}
	std::cout << std::endl;
	addArmies(ownedRegions[region], armiesLeft);
}

void Bot::makeMoves()
{
	std::vector<std::string> moves;
	if(ammutari)
	for (size_t i = 0; i < proiecte.size(); ++i)
		if(proiecte[i].movenr){
			std::stringstream move;
			// obs: eregions.Armies a fost modificat si nu mai este relevant !!
			move << botName << " attack/transfer " << proiecte[i].movefrom << " " << proiecte[i].moveto << " " << proiecte[i].movenr;
			moves.push_back(move.str());
		}
	if((ammutari == 0) || (proiecte.size() == 0))
		moves.push_back("No moves");
	proiecte.clear();
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
	rewardsuperregiuni[noSuperRegion] = reward;
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
}
void Bot::opponentMovement(const unsigned &noRegion, const unsigned &toRegion, const int &nbArmies)
{
	// suppress unused variable warnings
	(void) noRegion;
	(void) toRegion;
	(void) nbArmies;
}

void Bot::startDelay(const int& delay)
{
	// suppress unused variable warnings
	(void) delay;
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
