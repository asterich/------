#ifndef __MULTI_LIST_MANAGEMENT_H_
#define __MULTI_LIST_MANAGEMENT_H_

#include "sq_list.h"

typedef struct {  //线性表的管理表定义
    struct ListInfo {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
} LISTS;

// multi-list management
status AddList(LISTS &Lists, const char *ListName);
status RemoveList(LISTS &Lists, const char *ListName);
int LocateList(LISTS Lists, const char *ListName);

#endif