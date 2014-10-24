/*
 *  util.h
 *  MultidimensionalScaling
 *
 *  Created by Juan David CRUZ GOMEZ on 9/20/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include <matrix.h>
#include <vector>

#include "distance.h"
#include "distance_factory.h"

Matrix* createDissimilarityMatrix( std::vector<t_point*> point_set, int distance_type );

