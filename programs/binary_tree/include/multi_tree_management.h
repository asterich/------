#ifndef __MULTI_TREE_MANAGEMENT_H_
#define __MULTI_TREE_MANAGEMENT_H_

#include "binary_tree.h"

typedef struct {  //线性表的管理表定义
    struct TreeInfo {
        char name[30];
        BiTree L;
    } elem[10];
    int length;
    int listsize;
} MultiTreeTable;

status AddTree(MultiTreeTable &Trees, const char *TreeName);
status RemoveTree(MultiTreeTable &Trees, const char *TreeName);
int LocateTree(MultiTreeTable Trees, const char *TreeName);

#endif