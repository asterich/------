#include "binary_tree_impl.h"

/**
 * @brief Create a binary tree recursively by elements sequenced by preorder.
 * Just returns the element corresponding to rightest node in left subtree
 * so we can make use of that essence information.
 *
 * @param node The root of the tree/subtree
 * @param elem The pointer to the element corresponding to current node
 * @return TElemType*
 */
TElemType *create_binary_tree_by_preorder(BiTree &node, TElemType *elem) {
    if (elem->key == 0 || elem->key == -1) {
        node = NULL;
        return elem;
    } else {
        node = (BiTNode *)malloc(sizeof(BiTNode));
        node->data = *elem;
        TElemType *rightest =
            create_binary_tree_by_preorder(node->lchild, elem + 1);
        return create_binary_tree_by_preorder(node->rchild, rightest + 1);
    }
}

/**
 * @brief Check if there is any repeated key in %elems.
 *
 * @param elems
 * @return status
 */
status check_if_repeated_in_elems(const TElemType elems[]) {
    std::unordered_set<KeyType> keys;
    const TElemType *p_elem = elems;
    while (p_elem->key != -1) {
        if (keys.find(p_elem->key) != keys.end()) {
            return ERROR;
        }
        if (p_elem->key != 0) {
            keys.insert(p_elem->key);
        }
        ++p_elem;
    }
    return OK;
}

/**
 * @brief Helper function to clean the binary tree.
 *
 * @param T
 */
void clear_binary_tree(BiTree &T) {
    if (T == NULL) {
        return;
    }
    clear_binary_tree(T->lchild);
    clear_binary_tree(T->rchild);
    free(T);
    T = NULL;
    return;
}

int tree_depth(BiTree T) {
    if (!T) {
        return 0;
    }
    return std::max(tree_depth(T->lchild), tree_depth(T->rchild)) + 1;
}

BiTNode *locate_node(BiTree T, KeyType e) {
    if (!T) {
        return NULL;
    }
    if (T->data.key == e) {
        return T;
    }
    BiTNode *res_in_l = locate_node(T->lchild, e);
    BiTNode *res_in_r = locate_node(T->rchild, e);
    if (res_in_l) {
        return res_in_l;
    }
    if (res_in_r) {
        return res_in_r;
    }
    return NULL;
}

BiTNode *locate_node_if_changeable(BiTree T, KeyType target_key,
                                   TElemType elem_to_change) {
    BiTNode *target = locate_node(T, target_key);
    if (!target) {
        return NULL;
    }
    BiTNode *node_to_change = locate_node(T, elem_to_change.key);
    if (node_to_change && node_to_change != target) {
        return NULL;
    }
    return target;
}

BiTNode *locate_node_if_insertable(BiTree T, KeyType target_key,
                                   TElemType elem_to_insert) {
    BiTNode *target = locate_node(T, target_key);
    if (!target) {
        return NULL;
    }
    BiTNode *node_to_insert = locate_node(T, elem_to_insert.key);
    if (node_to_insert) {
        return NULL;
    }
    return target;
}

BiTNode *get_sibling(BiTree T, KeyType e) {
    if (!T) {
        return NULL;
    }
    if (T->lchild && T->lchild->data.key == e) {
        return T->rchild;
    } else if (T->rchild && T->rchild->data.key == e) {
        return T->lchild;
    }
    BiTNode *res_in_l = get_sibling(T->lchild, e);
    BiTNode *res_in_r = get_sibling(T->rchild, e);
    if (res_in_l) {
        return res_in_l;
    } else if (res_in_r) {
        return res_in_r;
    }
    return T;
}

BiTNode *get_father(BiTree T, KeyType e) {
    if (!T) {
        return NULL;
    }
    if (T->lchild && T->lchild->data.key == e) {
        return T;
    } else if (T->rchild && T->rchild->data.key == e) {
        return T;
    }
    BiTNode *res_in_l = get_father(T->lchild, e);
    BiTNode *res_in_r = get_father(T->rchild, e);
    if (res_in_l) {
        return res_in_l;
    } else if (res_in_r) {
        return res_in_r;
    }
    return NULL;
}

BiTNode *get_rightest_node(BiTree T) {
    if (T->rchild) {
        return get_rightest_node(T->rchild);
    } else if (T->lchild) {
        return get_rightest_node(T->lchild);
    } else {
        return T;
    }
}

BiTNode *get_leftest_node(BiTree T) {
    if (T->lchild) {
        return get_leftest_node(T->lchild);
    } else if (T->rchild) {
        return get_leftest_node(T->rchild);
    } else {
        return T;
    }
}

status insert_node(BiTree &node, int LR, TElemType c) {
    BiTNode *new_node = (BiTNode *)malloc(sizeof(BiTNode));
    if (!new_node) {
        return ERROR;
    }
    new_node->lchild = NULL;
    switch (LR) {
        case 0: {
            new_node->rchild = node->lchild;
            node->lchild = new_node;
        } break;
        case 1: {
            new_node->rchild = node->rchild;
            node->rchild = new_node;
        } break;
        case -1: {  // insert as root; ignoring %node's parent node
            new_node->rchild = node;
            node = new_node;
        } break;
    }
    new_node->data = c;
    return OK;
}

status delete_node(BiTree &root, KeyType e) {
    if (root->data.key == e) {
        BiTNode *target = root;
        if (!target->lchild && !target->rchild) {
            free(target);
            root = NULL;
        } else if ((!target->lchild && target->rchild) ||
                   (target->lchild && !target->rchild)) {
            BiTNode *target_child =
                target->lchild ? target->lchild : target->rchild;
            root = target_child;
            free(target);
        } else {
            BiTNode *target_child = target->lchild;
            BiTNode *rightest_node = get_rightest_node(target_child);
            rightest_node->rchild = target->rchild;
            free(target);
            root = target_child;
        }
    } else {
        BiTNode *father = get_father(root, e);
        BiTNode **p_target = &((father->lchild && e == father->lchild->data.key)
                                   ? father->lchild
                                   : father->rchild);
        if (!(*p_target)->lchild && !(*p_target)->rchild) {
            free(*p_target);
            *p_target = NULL;
        } else if ((!(*p_target)->lchild && (*p_target)->rchild) ||
                   ((*p_target)->lchild && !(*p_target)->rchild)) {
            BiTNode *target_child =
                (*p_target)->lchild ? (*p_target)->lchild : (*p_target)->rchild;
            free(*p_target);
            *p_target = target_child;
        } else {
            BiTNode *target_child = (*p_target)->lchild;
            BiTNode *rightest_node = get_rightest_node(target_child);
            rightest_node->rchild = (*p_target)->rchild;
            free(*p_target);
            *p_target = target_child;
        }
    }
    return OK;
}

status traverse_in_preorder(BiTree root, void (*visit)(BiTree)) {
    std::stack<BiTNode *> node_stack;
    node_stack.push(root);
    while (!node_stack.empty()) {
        BiTNode *current_node = node_stack.top();
        node_stack.pop();
        visit(current_node);
        if (current_node->rchild) {
            node_stack.push(current_node->rchild);
        }
        if (current_node->lchild) {
            node_stack.push(current_node->lchild);
        }
    }
    return OK;
}

status traverse_in_inorder(BiTree root, void (*visit)(BiTree)) {
    std::stack<BiTNode *> node_stack;
    std::unordered_set<BiTNode *> visited;
    node_stack.push(root);
    while (!node_stack.empty()) {
        BiTNode *current_node = node_stack.top();
        if (current_node->lchild &&
            visited.find(current_node->lchild) == visited.end()) {
            node_stack.push(current_node->lchild);
        } else {
            visit(current_node);
            visited.insert(current_node);
            node_stack.pop();
            if (current_node->rchild) {
                node_stack.push(current_node->rchild);
            }
        }
    }
    return OK;
}

status traverse_in_postorder(BiTree root, void (*visit)(BiTree)) {
    std::stack<BiTNode *> node_stack1, node_stack2;
    node_stack1.push(root);
    while (!node_stack1.empty()) {
        BiTNode *current_node = node_stack1.top();
        node_stack1.pop();
        node_stack2.push(current_node);
        if (current_node->lchild) {
            node_stack1.push(current_node->lchild);
        }
        if (current_node->rchild) {
            node_stack1.push(current_node->rchild);
        }
    }
    while (!node_stack2.empty()) {
        BiTNode *current_node = node_stack2.top();
        node_stack2.pop();
        visit(current_node);
    }
    return OK;
}

status traverse_in_levelorder(BiTree root, void (*visit)(BiTree)) {
    std::deque<BiTNode *> node_queue;
    node_queue.push_back(root);
    while (!node_queue.empty()) {
        BiTNode *current_node = node_queue.front();
        node_queue.pop_front();
        visit(current_node);
        if (current_node->lchild) {
            node_queue.push_back(current_node->lchild);
        }
        if (current_node->rchild) {
            node_queue.push_back(current_node->rchild);
        }
    }
    return OK;
}

status save_to_file(BiTree root, char filename[]) {
    std::fstream s(filename, std::fstream::binary | std::fstream::trunc |
                                 std::fstream::in | std::fstream::out);
    if (!s.is_open()) {
        return ERROR;
    }
    std::stack<BiTNode *> node_stack;
    node_stack.push(root);
    while (!node_stack.empty()) {
        BiTNode *current_node = node_stack.top();
        node_stack.pop();
        if (current_node) {
            s.write(reinterpret_cast<char *>(&current_node->data),
                    sizeof current_node->data);
            node_stack.push(current_node->rchild);
            node_stack.push(current_node->lchild);
        } else {
            TElemType tmp;
            tmp.key = 0;
            strcpy(tmp.others, "null");
            s.write(reinterpret_cast<char *>(&tmp), sizeof tmp);
        }
    }
    return OK;
}

status load_from_file(BiTree &root, char filename[]) {
    FILE *fp = fopen(filename, "ra+");
    if (!fp) {
        return ERROR;
    }
    TElemType *elem_buf = (TElemType *)malloc(1000 * sizeof(TElemType));
    if (!elem_buf) {
        return ERROR;
    }
    fread(elem_buf, sizeof(TElemType), 1000, fp);
    create_binary_tree_by_preorder(root, elem_buf);
    free(elem_buf);
    return OK;
}

status invert(BiTree &T) {
    if (!T) {
        return OK;
    }
    BiTNode *tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    invert(T->lchild);
    invert(T->rchild);
    return OK;
}

KeyType max_path_sum(BiTree T) {
    if (!T) {
        return 0;
    }
    return T->data.key +
           std::max(max_path_sum(T->lchild), max_path_sum(T->rchild));
}

std::unordered_map<BiTNode *, std::array<BiTNode *, 32>> father;
std::unordered_map<BiTNode *, int> depth;

void init(BiTree root) {
    father.clear();
    depth.clear();

    father.insert(std::pair<BiTNode *, std::array<BiTNode *, 32>>{
        NULL, std::array<BiTNode *, 32>()});
    father.insert(std::pair<BiTNode *, std::array<BiTNode *, 32>>{
        root, std::array<BiTNode *, 32>()});
    for (auto &[k, arr] : father) {
        arr.fill(NULL);
    }
    depth.insert(std::pair<BiTNode *, int>{NULL, 0});
}

void dfs(BiTNode *node, BiTNode *fa_node) {
    if (!node) {
        return;
    }
    father[node][0] = fa_node;
    depth[node] = depth[father[node][0]] + 1;
    for (int i = 1; i < 31; ++i) {
        father[node][i] = father[father[node][i - 1]][i - 1];
    }
    dfs(node->lchild, node);
    dfs(node->rchild, node);
    return;
}

BiTNode *lca(BiTree T, BiTNode *n1, BiTNode *n2) {
    init(T);
    dfs(T, NULL);
    if (depth[n1] > depth[n2]) {
        std::swap(n1, n2);
    }
    int delta = depth[n2] - depth[n1];
    for (int j = 0; delta; ++j, delta >>= 1) {
        if (delta & 1) {
            n2 = father[n2][j];
        }
    }
    if (n2 == n1) return n2;
    for (int j = 30; j >= 0 && n2 != n1; --j) {
        if (father[n2][j] != father[n1][j]) {
            n2 = father[n2][j];
            n1 = father[n1][j];
        }
    }
    n2 = father[n2][0];
    n1 = father[n1][0];
    return n2;
}