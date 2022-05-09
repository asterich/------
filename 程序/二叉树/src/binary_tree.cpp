#include <algorithm>
#include <unordered_set>

#include "binary_tree.h"
#include "binary_tree_impl.h"

/**
 * @brief Create a binary tree.
 *
 * @param T Tree to be created
 * @param definition Elements to be added into the tree
 * @return status
 */
status CreateBiTree(BiTree &T, TElemType definition[]) {
    T = NULL;
    if (check_if_repeated_in_elems(definition) != OK) {
        return ERROR;
    }
    create_binary_tree_by_preorder(T, definition);
    return OK;
}

/**
 * @brief Clean the binary tree %T.
 *
 * @param T
 * @return status
 */
status ClearBiTree(BiTree &T) {
    clear_binary_tree(T);
    T = NULL;
    return OK;
}

/**
 * @brief Return the depth of a tree.
 *
 * @param T
 * @return int
 */
int BiTreeDepth(BiTree T) { return tree_depth(T); }

/**
 * @brief Locate a node.
 *
 * @param T
 * @param e
 * @return BiTNode*
 */
BiTNode *LocateNode(BiTree T, KeyType e) { return locate_node(T, e); }

/**
 * @brief Assign a value to a node.
 *
 * @param T
 * @param e
 * @param value
 * @return status
 */
status Assign(BiTree &T, KeyType e, TElemType value) {
    BiTNode *target = locate_node_if_changeable(T, e, value);
    if (!target) {
        return ERROR;
    }
    target->data = value;
    return OK;
}

/**
 * @brief Get the sibling of a node.
 *
 * @param T
 * @param e
 * @return BiTNode*
 */
BiTNode *GetSibling(BiTree T, KeyType e) { return get_sibling(T, e); }

/**
 * @brief Insert a node to the node with key %e. If LR == 0, insert as
 * left child; if LR == 1, insert as right child; if LR == -1, insert as
 * the root of the whole tree. The original node is set as the right
 * subtree of the new node.
 *
 * @param T
 * @param e
 * @param LR
 * @param c
 * @return status
 */
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c) {
    status s = OK;
    BiTNode *target = LR == -1 ? T : locate_node_if_insertable(T, e, c);
    if (!target) {
        return ERROR;
    }
    s = insert_node(target, LR, c);
    if (s == ERROR) {
        return s;
    }
    if (LR == -1) {
        T = target;
    }
    return OK;
}

/**
 * @brief Delete a node.
 * If the outward degree of the node is 0, just delete it;
 * if the degree is 1, replace the node with its child;
 * if the degree is 2, replace the node with its left child,
 * and set its right child as the right child of the rightest node
 * in its left subtree.
 *
 * @param T
 * @param e
 * @return status
 */
status DeleteNode(BiTree &T, KeyType e) {
    BiTNode *target = locate_node(T, e);
    if (!target) {
        return ERROR;
    }
    delete_node(T, e);
    return OK;
}

/**
 * @brief Traverse a tree in preorder. Each time a node is visited,
 * adapt the function %visit to it.
 *
 * @param T
 * @param visit
 * @return status
 */
status PreOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (!T) {
        return ERROR;
    }
    traverse_in_preorder(T, visit);
    return OK;
}

/**
 * @brief Traverse a tree in inorder. Each time a node is visited,
 * adapt the function %visit to it.
 *
 * @param T
 * @param visit
 * @return status
 */
status InOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (!T) {
        return ERROR;
    }
    traverse_in_inorder(T, visit);
    return OK;
}
/**
 * @brief Traverse a tree in postorder. Each time a node is visited,
 * adapt the function %visit to it.
 *
 * @param T
 * @param visit
 * @return status
 */
status PostOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (!T) {
        return ERROR;
    }
    traverse_in_postorder(T, visit);
    return OK;
}

/**
 * @brief Traverse a tree in level order. Each time a node is visited,
 * adapt the function %visit to it.
 *
 * @param T
 * @param visit
 * @return status
 */
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (!T) {
        return ERROR;
    }
    traverse_in_levelorder(T, visit);
    return OK;
}

/**
 * @brief Save a tree to a file.
 *
 * @param T
 * @param FileName
 * @return status
 */
status SaveBiTree(BiTree T, char FileName[]) {
    return save_to_file(T, FileName);
}

/**
 * @brief Load a tree from a file.
 *
 * @param T
 * @param FileName
 * @return status
 */
status LoadBiTree(BiTree &T, char FileName[]) {
    return load_from_file(T, FileName);
}

/**
 * @brief Invert a tree. That means swap the left child
 * and the right child of each node.
 *
 * @param T
 * @return status
 */
status InvertTree(BiTree &T) { return invert(T); }

/**
 * @brief Make max path sum of a tree from its root node.
 *
 * @param T
 * @return status
 */
status MaxPathSum(BiTree T) { return max_path_sum(T); }

/**
 * @brief Return the lca of two nodes.
 *
 * @param T
 * @param e1
 * @param e2
 * @return BiTNode*
 */
BiTNode *LowestCommonAncestor(BiTree T, BiTNode *e1, BiTNode *e2) {
    return lca(T, e1, e2);
}