#include "MapSearch.h"

MapSearch::MapSearch()
{
	// nothing to do
}

MapSearch::~MapSearch()
{
	// nothing to do
}

MapSearch& MapSearch::get_instance()
{
	static MapSearch instance;
	return instance;
}

Region MapSearch::get_closest_front(const Region& region)
{
	// perform BFS until I find a front
	std::vector<bool> discovered(regions.size(), false);
	std::queue<Region> toVisit;
	toVisit.push(region);
	discovered[region.getId()] = true;
	while(!toVisit.empty()) {
		Region currentRegion = toVisit.front();
		
		toVisit.pop();
		for (int i = 0; i < currentRegion.getNbNeighbors() ; ++i)
		{
			if(discovered[i] == false) {
				Region nextRegion = regions[currentRegion.getNeighbor(i)];
				if(nextRegion.getOwner() != ME)
					return currentRegion;
				toVisit.push(nextRegion);
				discovered[i] = true;
			}
		}
	}
	Region x;
	return x;
}

unsigned MapSearch::get_min_distance(const Region& fromRegion, const Region& toRegion, unsigned distance = 0)
{
	srcId = fromRegion.getId();
	dstId = toRegion.getId();


	if(distances[srcId][dstId] != NOT_SET)
		return distances[srcId][dstId] + distance;
	// perform DFS to find the distance;
	if(srcId == dstId)
		return distance;
	for (int i = 0; i < fromRegion.getNbNeighbors; ++i)
	{
		get_min_distance(fromRegion.getNeighbor(i), toRegion, distance + 1);
	}
}

std::vector<unsigned> MapSearch::road_to(const unsigned& fromRegion, const unsigned& toRegion)
{
	//TODO Dijkstra, maybe?
	std::vector<unsigned> result;
	return result;
}