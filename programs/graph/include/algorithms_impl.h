#ifndef __ALGORITHMS_IMPL_H__
#define __ALGORITHMS_IMPL_H__

#include <cstdint>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

#include "graph.h"

std::vector<KeyType> dijkstra(ALGraph G, KeyType u);

int tarjan(ALGraph G);

int connected_components_cnt(ALGraph G);

#endif