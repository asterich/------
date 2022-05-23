#ifndef __MULTI_GRAPH_MANAGEMENT_IMPL_H__
#define __MULTI_GRAPH_MANAGEMENT_IMPL_H__

#include "multi_graph_management.h"

status append(MultiGraphTable &graph, const char *graph_name);
status remove(MultiGraphTable &graph, const char *graph_name);
int locate(MultiGraphTable &graph, const char *graph_name);

#endif