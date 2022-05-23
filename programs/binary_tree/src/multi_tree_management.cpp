#include "multi_tree_management.h"
#include "multi_tree_management_impl.h"

/**
 * @brief Add an uninitialized tree to a multi-tree table. The appended tree
 * needs to be "created" from a preorder sequence later.
 *
 * @param Trees
 * @param TreeName
 * @return status
 */
status AddTree(MultiTreeTable &Trees, const char *TreeName) {
    return append(Trees, TreeName);
}

/**
 * @brief Remove a tree from a multi-tree table.
 *
 * @param Trees
 * @param TreeName
 * @return status
 */
status RemoveTree(MultiTreeTable &Trees, const char *TreeName) {
    return remove(Trees, TreeName);
}

/**
 * @brief Locate the position of the tree with given name %TreeName.
 *
 * @param Trees
 * @param TreeName
 * @return int
 */
int LocateTree(MultiTreeTable Trees, const char *TreeName) {
    return locate(Trees, TreeName);
}