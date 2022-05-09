#ifndef __GRAPH_IMPL_H__
#define __GRAPH_IMPL_H__

#include <queue>
#include <stack>
#include <unordered_set>

#include "graph.h"

status create_graph(ALGraph &graph, VertexType vertices_info[],
                    KeyType edges[][3]);
status destroy_graph(ALGraph &graph);

int locate_vertex(ALGraph &graph, KeyType u);
status assign_to_vertex(ALGraph &graph, KeyType u, VertexType value);
status append_vertex(ALGraph &graph, VertexType value);
status remove_vertex(ALGraph &graph, KeyType u);

status is_one_way_edge_exist(ALGraph graph, KeyType u, KeyType v);
status append_one_way_edge(ALGraph &graph, KeyType u, KeyType v, int w);
status remove_one_way_edge(ALGraph &graph, KeyType u, KeyType v);

status dfs(ALGraph &graph, void (*visit)(VertexType));
status bfs(ALGraph &graph, void (*visit)(VertexType));

status save(ALGraph graph, char filename[]);
status load(ALGraph &graph, char filename[]);

#endif
