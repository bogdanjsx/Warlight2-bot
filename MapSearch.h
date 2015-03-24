#ifndef MAPSEARCH_H
#define MAPSEARCH_H

// stl
#include <vector>
#include <queue>

// project
#include "Bot.h"
#include "main.h"
#include "Parser.h"
#include "Region.h"
#include "SuperRegion.h"

// constants
#define NOT_SET -1

class MapSearch
{

public:
	/**
	 * Returns the shared singleton instance
	 * @return The shared instance
	 */
	static MapSearch& get_instance();
	/**
	 * Calculates the closest front to a region
	 * @param Region to calculate closest front
	 * @return Region which is closest front
	 */
	Region get_closest_front(const Region& region);
	/**
	 * Calculates minimum distance between 2 regions
	 * @param ID of source region
	 * @param ID of destination region
	 * @return Number of regions to be traversed between the 2 parameters
	 */
	unsigned get_min_distance(const Region& fromRegion, const Region& toRegion, unsigned distance = 0);
	/**
	 * Gets all the regions on the shortest road between 2 regions
	 * @param Source region
	 * @param frontDistancesestination region
	 * @return A vector containing IDs of all regions on the road
	 */
	std::vector<unsigned> road_to(const unsigned& fromRegion, const unsigned& toRegion);

private:
	std::vector<unsigned> frontDistances;
	std::vector<std::vector<unsigned> > distances;
	// holds minimum roads after they are calculated
	std::vector<std::vector<unsigned> > roads;
	std::vector<Region> regions;

	MapSearch();
	virtual ~MapSearch();

	MapSearch(MapSearch const&)			= delete;
    void operator=(MapSearch const&)	= delete;
};

#endif // MAPSEARCH_H