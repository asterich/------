#include "graph.h"
#include "graph_impl.h"

status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][3]) {
    return create_graph(G, V, VR);
}

status DestroyGraph(ALGraph &G) { return destroy_graph(G); }

int LocateVex(ALGraph G, KeyType u) { return locate_vertex(G, u); }

status PutVex(ALGraph &G, KeyType u, VertexType value) {
    return assign_to_vertex(G, u, value);
}

status InsertVex(ALGraph &G, VertexType v) { return append_vertex(G, v); }

status DeleteVex(ALGraph &G, KeyType v) { return remove_vertex(G, v); }

int FirstAdjVex(ALGraph G, KeyType u) {
    int pos_u = locate_vertex(G, u);
    if (pos_u == -1) {
        return pos_u;
    }
    if (!G.vertices[pos_u].firstarc) {
        return -1;
    }
    return G.vertices[pos_u].firstarc->adjvex;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w) {
    int pos_v = locate_vertex(G, v), pos_w = locate_vertex(G, w);
    if (pos_v == -1 || pos_w == -1) {
        return -1;
    }
    ArcNode *p = G.vertices[pos_v].firstarc;
    int res = -1;
    while (p) {
        if (p->adjvex == pos_w) {
            if (!p->nextarc) {
                return -1;
            }
            res = p->nextarc->adjvex;
        }
        p = p->nextarc;
    }
    return res;
}

status InsertArc(ALGraph &G, KeyType v, KeyType w, int weight) {
    status s = is_one_way_edge_exist(G, v, w);
    if (s == OK) {
        return ERROR;
    }
    s = append_one_way_edge(G, v, w, weight);
    if (s == ERROR) {
        return ERROR;
    }
    s = append_one_way_edge(G, w, v, weight);
    if (s == ERROR) {
        return ERROR;
    }
    ++G.arcnum;
    return OK;
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w) {
    status s = is_one_way_edge_exist(G, v, w);
    if (s == ERROR) {
        return ERROR;
    }
    s = remove_one_way_edge(G, v, w);
    if (s == ERROR) {
        return ERROR;
    }
    s = remove_one_way_edge(G, w, v);
    if (s == ERROR) {
        return ERROR;
    }
    --G.arcnum;
    return OK;
}

status DFSTraverse(ALGraph &G, void (*visit)(VertexType)) {
    return dfs(G, visit);
}

status BFSTraverse(ALGraph &G, void (*visit)(VertexType)) {
    return bfs(G, visit);
}

status SaveGraph(ALGraph G, char FileName[]) { return save(G, FileName); }

status LoadGraph(ALGraph &G, char FileName[]) { return load(G, FileName); }
