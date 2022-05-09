#ifndef __BINARY_TREE_IMPL_H_
#define __BINARY_TREE_IMPL_H_

#include <algorithm>
#include <array>
#include <cstdio>
#include <deque>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "binary_tree.h"

TElemType *create_binary_tree_by_preorder(BiTree &node, TElemType *elem);
status check_if_repeated_in_elems(const TElemType elems[]);
void clear_binary_tree(BiTree &T);

int tree_depth(BiTree T);
BiTNode *locate_node(BiTree T, KeyType e);
BiTNode *locate_node_if_changeable(BiTree T, KeyType target_key,
                                   TElemType elem_to_change);
BiTNode *locate_node_if_insertable(BiTree T, KeyType target_key,
                                   TElemType elem_to_insert);
BiTNode *get_sibling(BiTree T, KeyType e);
BiTNode *get_father(BiTree T, KeyType e);
BiTNode *get_rightest_node(BiTree T);
BiTNode *get_leftest_node(BiTree T);

status insert_node(BiTree &node, int LR, TElemType c);
status delete_node(BiTree &root, KeyType e);

status traverse_in_preorder(BiTree root, void (*visit)(BiTree));
status traverse_in_inorder(BiTree root, void (*visit)(BiTree));
status traverse_in_postorder(BiTree root, void (*visit)(BiTree));
status traverse_in_levelorder(BiTree root, void (*visit)(BiTree));

status save_to_file(BiTree root, char filename[]);
status load_from_file(BiTree &root, char filename[]);

status invert(BiTree &T);
KeyType max_path_sum(BiTree T);
BiTNode *lca(BiTree T, BiTNode *n1, BiTNode *n2);

#endif
