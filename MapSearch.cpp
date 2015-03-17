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

unsigned MapSearch::get_closest_front(const unsigned& region)
{
	return frontDistances[region];
}

unsigned MapSearch::get_min_distance(const unsigned& fromRegion, const unsigned& toRegion){
	return distances[fromRegion][toRegion];
}

std::vector<unsigned> MapSearch::road_to(const unsigned& fromRegion, const unsigned& toRegion) {
	//TODO Dijkstra, maybe?
	std::vector<unsigned> result;
	return result;
}