#ifndef MAPSEARCH_H
#define MAPSEARCH_H

// stl
#include <vector>


// project
#include "Bot.h"
#include "main.h"
#include "Parser.h"
#include "Region.h"
#include "SuperRegion.h"

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
	 * @param ID of the region to calculate closest front
	 * @return ID of the closest front
	 */
	unsigned get_closest_front(const unsigned& region);
	/**
	 * Calculates minimum distance between 2 regions
	 * @param ID of source region
	 * @param ID of destination region
	 * @return Number of regions to be traversed between the 2 parameters
	 */
	unsigned get_min_distance(const unsigned& fromRegion, const unsigned& toRegion);
	/**
	 * Gets all the regions on the shortest road between 2 regions
	 * @param ID of source region
	 * @param ID of destination region
	 * @return A vector containing IDs of all regions on the road
	 */
	std::vector<unsigned> road_to(const unsigned& fromRegion, const unsigned& toRegion);

private:
	std::vector<unsigned> frontDistances;
	std::vector<std::vector<unsigned> > distances;
	// holds minimum roads after they are calculated
	std::vector<std::vector<unsigned> > roads;

	MapSearch();
	virtual ~MapSearch();

	MapSearch(MapSearch const&)			= delete;
    void operator=(MapSearch const&)	= delete;
};

#endif // MAPSEARCH_H