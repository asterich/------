#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
    KeyType key;
    char others[20];
} VertexType;  //顶点类型定义

typedef struct ArcNode {      //表结点类型定义
    int adjvex;               //顶点位置编号
    int w;                    //边权
    struct ArcNode *nextarc;  //下一个表结点指针
} ArcNode;

typedef struct VNode {  //头结点及其数组类型定义
    VertexType data;    //顶点信息
    ArcNode *firstarc;  //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {         //邻接表的类型定义
    AdjList vertices;    //头结点数组
    int vexnum, arcnum;  //顶点数、弧数
    GraphKind kind;      //图的类型
} ALGraph;

status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][3]);
status DestroyGraph(ALGraph &G);

int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph &G, KeyType u, VertexType value);
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, KeyType v);

int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);

status InsertArc(ALGraph &G, KeyType v, KeyType w, int weight);
status DeleteArc(ALGraph &G, KeyType v, KeyType w);

status DFSTraverse(ALGraph &G, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));

status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);

#endif