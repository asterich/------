#ifndef __SQ_LIST_H_
#define __SQ_LIST_H_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
/*
#define OVERFLOW -2
*/

typedef int status;
typedef int ElemType;  //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct {  //顺序表（顺序结构）的定义
    ElemType *elem;
    int length;
    int listsize;
} SqList;

// init and destroy operations
status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);

// memory operations
status ReallocList(SqList &L, size_t new_size);

// list info
status ListEmpty(SqList L);
status ListLength(SqList L);
status ListTraverse(SqList L);

// elem operations
status GetElem(SqList L, int i, ElemType &e);
int LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType e, ElemType &pre);
status NextElem(SqList L, ElemType e, ElemType &next);

// list change operations
status ListInsert(SqList &L, int i, ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);

// file i/o operations
status SaveList(SqList L, char FileName[]);
status LoadList(SqList &L, char FileName[]);

#endif