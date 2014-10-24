#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <tulip/Graph.h>
#include <tulip/ColorProperty.h>

#include <vector>

#include "colorwheel.h"

using namespace tlp;
using namespace std;

/**
 * Takes a parititon and set a color for each group in it
 * @param thegraph the graph object containing the partition
 */
void color_partitions( Graph* theGraph );
/**
 * Remove all the groups of size 0 from the partition
 * @param thegraph the graph object containing the partition
 */
void clean_partition( Graph* theGraph );

#endif