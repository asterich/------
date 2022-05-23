#ifndef __MULTI_GRAPH_MANAGEMENT_H__
#define __MULTI_GRAPH_MANAGEMENT_H__

#include "graph.h"

enum GraphStatus { NOT_CREATED, CREATED };

typedef struct {  //线性表的管理表定义
    struct GraphInfo {
        char name[30];
        ALGraph G;
        GraphStatus g_status;
    } elem[10];
    int length;
    int listsize;
} MultiGraphTable;

status AddGraph(MultiGraphTable &Graphs, const char *GraphName);
status RemoveGraph(MultiGraphTable &Graphs, const char *GraphName);
int LocateGraph(MultiGraphTable Graphs, const char *GraphName);

#endif