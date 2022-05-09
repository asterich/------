#include "multi_graph_management.h"
#include "multi_graph_management_impl.h"

/**
 * @brief Add a blank graph to a multi-graph table. The appended graph
 * needs to be "created" from a preorder sequence later.
 *
 * @param Graphs
 * @param GraphName
 * @return status
 */
status AddGraph(MultiGraphTable &Graphs, const char *GraphName) {
    return append(Graphs, GraphName);
}

/**
 * @brief Remove a graph from a multi-graph table.
 *
 * @param Graphs
 * @param GraphName
 * @return status
 */
status RemoveGraph(MultiGraphTable &Graphs, const char *GraphName) {
    return remove(Graphs, GraphName);
}

/**
 * @brief Locate the position of the graph with given name %GraphName.
 *
 * @param Graphs
 * @param GraphName
 * @return int
 */
int LocateGraph(MultiGraphTable Graphs, const char *GraphName) {
    return locate(Graphs, GraphName);
}