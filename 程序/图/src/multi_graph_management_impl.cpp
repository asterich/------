#include "multi_graph_management_impl.h"

status append(MultiGraphTable &graphs, const char *graph_name) {
    if (graphs.length > graphs.listsize || graphs.length < 0) {
        return ERROR;
    }

    graphs.elem[graphs.length].g_status = GraphStatus::NOT_CREATED;

    strcpy(graphs.elem[graphs.length++].name, graph_name);
    return OK;
}

status remove(MultiGraphTable &graphs, const char *graph_name) {
    if (graphs.length <= 0) {
        return ERROR;
    }

    int pos = -1;
    for (int i = 1; i <= graphs.length; i++) {
        if (strcmp(graph_name, graphs.elem[i - 1].name) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        return ERROR;
    }

    DestroyGraph(graphs.elem[pos - 1].G);
    graphs.elem[pos - 1].g_status = GraphStatus::NOT_CREATED;
    for (int i = pos; i <= graphs.length; i++) {
        graphs.elem[i - 1] = graphs.elem[i];
    }

    memset(&graphs.elem[graphs.length - 1], 0, sizeof(char));
    --graphs.length;

    return OK;
}

int locate(MultiGraphTable &graphs, const char *graph_name) {
    if (graphs.length <= 0) {
        return ERROR;
    }

    int pos = -1;
    for (int i = 1; i <= graphs.length; i++) {
        if (strcmp(graph_name, graphs.elem[i - 1].name) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        return ERROR;
    }

    return pos;
}
