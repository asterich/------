#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <ranges>
#include <vector>

#include "algorithms_impl.h"
#include "graph.h"

std::vector<int> VerticesSetLessThanK(ALGraph G, KeyType v, int k);

int ShortestPathLength(ALGraph G, KeyType v, KeyType w);

int ConnectedComponentsNums(ALGraph G);

#endif