#include "multi_tree_management_impl.h"

status append(MultiTreeTable &trees, const char *tree_name) {
    if (trees.length > trees.listsize || trees.length < 0) {
        return ERROR;
    }
    trees.elem[trees.length].L = NULL;
    strcpy(trees.elem[trees.length++].name, tree_name);
    return OK;
}

status remove(MultiTreeTable &trees, const char *tree_name) {
    if (trees.length <= 0) {
        return ERROR;
    }

    int pos = -1;
    for (int i = 1; i <= trees.length; i++) {
        if (strcmp(tree_name, trees.elem[i - 1].name) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        return ERROR;
    }

    ClearBiTree(trees.elem[pos - 1].L);
    for (int i = pos; i <= trees.length; i++) {
        trees.elem[i - 1] = trees.elem[i];
    }

    trees.elem[trees.length - 1].L = NULL;
    memset(trees.elem[trees.length - 1].name, 0, sizeof(char));
    --trees.length;

    return OK;
}

status locate(MultiTreeTable &trees, const char *tree_name) {
    if (trees.length <= 0) {
        return ERROR;
    }

    int pos = -1;
    for (int i = 1; i <= trees.length; i++) {
        if (strcmp(tree_name, trees.elem[i - 1].name) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        return ERROR;
    }

    return pos;
}
