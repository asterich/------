#ifndef __BINARY_TREE_H_
#define __BINARY_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
// #define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct {
    KeyType key;
    char others[20];
} TElemType;  //二叉树结点类型定义

typedef struct BiTNode {  //二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

status CreateBiTree(BiTree &T, TElemType definition[]);
status ClearBiTree(BiTree &T);

int BiTreeDepth(BiTree T);
BiTNode *LocateNode(BiTree T, KeyType e);
status Assign(BiTree &T, KeyType e, TElemType value);
BiTNode *GetSibling(BiTree T, KeyType e);

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree &T, KeyType e);

status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);

status InvertTree(BiTree &T);
status MaxPathSum(BiTree T);
BiTNode *LowestCommonAncestor(BiTree T, BiTNode *e1, BiTNode *e2);

#endif