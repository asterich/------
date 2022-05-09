#include "graph_impl.h"

status chk_if_vertices_repeated(VertexType vertices_info[]) {
    std::unordered_set<KeyType> k;
    VertexType *p_v = vertices_info;
    while (p_v->key != -1) {
        if (k.find(p_v->key) != k.end()) {
            return ERROR;
        }
        k.insert(p_v->key);
        ++p_v;
    }
    return OK;
}

status create_graph(ALGraph &graph, VertexType vertices_info[],
                    KeyType edges[][3]) {
    graph.vexnum = 0;
    graph.arcnum = 0;

    if (!vertices_info || vertices_info[0].key == -1) {
        return ERROR;
    }

    status s = chk_if_vertices_repeated(vertices_info);
    if (s == ERROR) {
        return ERROR;
    }

    VertexType *p_v = vertices_info;
    VNode *p_g = graph.vertices;
    while (p_v->key != -1 && graph.vexnum <= MAX_VERTEX_NUM) {
        memcpy(&p_g->data, p_v, sizeof(VertexType));
        p_g->firstarc = NULL;
        ++p_v;
        ++p_g;
        ++graph.vexnum;
    }
    if (graph.vexnum > MAX_VERTEX_NUM) {
        return ERROR;
    }

    KeyType(*p_e)[3] = edges;
    while ((*p_e)[0] != -1) {
        int u = (*p_e)[0], v = (*p_e)[1], w = (*p_e)[2];
        s = append_one_way_edge(graph, u, v, w);
        if (s == ERROR) {
            return ERROR;
        }
        s = append_one_way_edge(graph, v, u, w);
        if (s == ERROR && u != v) {  // `u != v` judges if the vertex is a loop
            return ERROR;
        }
        ++p_e;
        ++graph.arcnum;
    }

    return OK;
}

status destroy_graph(ALGraph &graph) {
    for (int i = 0; i < graph.vexnum; ++i) {
        ArcNode *p = graph.vertices[i].firstarc;
        while (p) {
            ArcNode *tmp = p;
            p = p->nextarc;
            free(tmp);
        }
    }
    memset(graph.vertices, 0, graph.vexnum * sizeof(VNode));
    graph.vexnum = graph.arcnum = 0;
    return OK;
}

int locate_vertex(ALGraph &graph, KeyType u) {
    VNode *p_g = graph.vertices;
    int index = 0;
    while (p_g->data.key != u && index < graph.vexnum) {
        ++p_g;
        ++index;
    }
    if (index >= graph.vexnum) {  // 没找到
        return -1;
    }
    return index;
}

status assign_to_vertex(ALGraph &graph, KeyType u, VertexType value) {
    int pos_u = locate_vertex(graph, u);
    if (pos_u == -1) {
        return ERROR;
    }

    int pos_new = locate_vertex(graph, value.key);
    if (pos_new != -1 && pos_new != pos_u) {
        return ERROR;
    }

    memcpy(&graph.vertices[pos_u].data, &value, sizeof(value));
    return OK;
}

status append_vertex(ALGraph &graph, VertexType value) {
    if (graph.vexnum >= MAX_VERTEX_NUM) {
        return ERROR;
    }
    memcpy(&graph.vertices[graph.vexnum++].data, &value, sizeof(value));
    return OK;
}

status remove_vertex(ALGraph &graph, KeyType u) {
    if (graph.vexnum <= 1) {
        return ERROR;
    }

    int pos_u = locate_vertex(graph, u);
    if (pos_u == -1) {
        return ERROR;
    }

    ArcNode *p = graph.vertices[pos_u].firstarc;
    while (p) {
        if (graph.vertices[p->adjvex].data.key != u) {
            status s = remove_one_way_edge(
                graph, graph.vertices[p->adjvex].data.key, u);
            if (s == ERROR) {
                return ERROR;
            }
        }
        ArcNode *tmp = p;
        p = p->nextarc;
        free(tmp);
        --graph.arcnum;
    }

    graph.vertices[pos_u].firstarc = NULL;

    for (int i = 0; i < graph.vexnum; i++) {
        ArcNode *p1 = graph.vertices[i].firstarc;
        while (p1) {
            if (p1->adjvex > pos_u) {
                --p1->adjvex;
            }
            p1 = p1->nextarc;
        }
    }

    for (int i = pos_u; i < graph.vexnum; i++) {
        memcpy(&graph.vertices[i], &graph.vertices[i + 1], sizeof(VNode));
    }

    memset(&graph.vertices[graph.vexnum - 1], 0, sizeof(VNode));

    --graph.vexnum;

    return OK;
}

status is_one_way_edge_exist(ALGraph graph, KeyType u, KeyType v) {
    int pos_u = locate_vertex(graph, u), pos_v = locate_vertex(graph, v);
    if (pos_u == -1 || pos_v == -1) {
        return ERROR;
    }
    ArcNode *p = graph.vertices[pos_u].firstarc;
    while (p) {
        if (p->adjvex == pos_v) {
            return OK;
        }
        p = p->nextarc;
    }
    return ERROR;
}

status append_one_way_edge(ALGraph &graph, KeyType u, KeyType v, int w) {
    int pos_u = locate_vertex(graph, u), pos_v = locate_vertex(graph, v);
    if (pos_u == -1 || pos_v == -1) {
        return ERROR;
    }

    if (!graph.vertices[pos_u].firstarc) {
        graph.vertices[pos_u].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
        if (!graph.vertices[pos_u].firstarc) {
            return ERROR;
        }
        graph.vertices[pos_u].firstarc->adjvex = pos_v;
        graph.vertices[pos_u].firstarc->w = w;
        graph.vertices[pos_u].firstarc->nextarc = NULL;
        return OK;
    }

    ArcNode *next = graph.vertices[pos_u].firstarc;
    ArcNode *new_node = (ArcNode *)malloc(sizeof(ArcNode));
    if (!new_node) {
        return ERROR;
    }
    graph.vertices[pos_u].firstarc = new_node;
    new_node->nextarc = next;
    new_node->w = w;
    new_node->adjvex = pos_v;
    return OK;
}

status remove_one_way_edge(ALGraph &graph, KeyType u, KeyType v) {
    int pos_u = locate_vertex(graph, u), pos_v = locate_vertex(graph, v);
    if (pos_u == -1 || pos_v == -1) {
        return ERROR;
    }

    ArcNode *p = graph.vertices[pos_u].firstarc, *prev = NULL;

    if (p->adjvex == pos_v) {
        graph.vertices[pos_u].firstarc = p->nextarc;
        free(p);
        return OK;
    }

    while (p) {
        if (p->adjvex == pos_v) {
            break;
        }
        prev = p;
        p = p->nextarc;
    }

    if (!p) {
        return OK;
    }

    prev->nextarc = p->nextarc;
    free(p);

    return OK;
}

status dfs(ALGraph &graph, void (*visit)(VertexType)) {
    int visited_node[MAX_VERTEX_NUM + 1] = {};
    std::stack<KeyType> node_stack;
    int visited_node_cnt = 0;

    while (visited_node_cnt < graph.vexnum) {
        while (!node_stack.empty()) {
            KeyType current_node = node_stack.top();
            node_stack.pop();
            if (visited_node[current_node]) {
                continue;
            }
            visit(graph.vertices[current_node].data);
            visited_node[current_node] = 1;
            ++visited_node_cnt;
            KeyType buf[MAX_VERTEX_NUM + 1] = {};
            int node_num = 0;
            const ArcNode *p = graph.vertices[current_node].firstarc;
            while (p) {
                if (!visited_node[p->adjvex]) {
                    buf[node_num++] = p->adjvex;
                }
                p = p->nextarc;
            }
            for (int i = node_num - 1; i >= 0; --i) {
                node_stack.push(buf[i]);
            }
        }
        for (int i = 0; i < graph.vexnum; ++i) {
            if (!visited_node[i]) {
                node_stack.push(i);
                break;
            }
        }
    }
    return OK;
}

status bfs(ALGraph &graph, void (*visit)(VertexType)) {
    int visited_node[MAX_VERTEX_NUM + 1] = {};
    std::queue<KeyType> node_queue;
    int visited_node_cnt = 0;

    while (visited_node_cnt < graph.vexnum) {
        while (!node_queue.empty()) {
            KeyType current_node = node_queue.front();
            node_queue.pop();
            if (visited_node[current_node]) {
                continue;
            }
            visit(graph.vertices[current_node].data);
            visited_node[current_node] = 1;
            ++visited_node_cnt;
            const ArcNode *p = graph.vertices[current_node].firstarc;
            while (p) {
                if (!visited_node[p->adjvex]) {
                    node_queue.push(p->adjvex);
                }
                p = p->nextarc;
            }
        }
        for (int i = 0; i < graph.vexnum; ++i) {
            if (!visited_node[i]) {
                node_queue.push(i);
                break;
            }
        }
    }
    return OK;
}

status save(ALGraph graph, char filename[]) {
    FILE *fp = fopen(filename, "wb+");
    if (!fp) {
        return ERROR;
    }
    fwrite(&graph.vexnum, sizeof(int), 1, fp);
    for (int i = 0; i < graph.vexnum; i++) {
        fwrite(&graph.vertices[i].data, sizeof(VertexType), 1, fp);
        ArcNode *p = graph.vertices[i].firstarc;
        while (p) {
            fwrite(&p->adjvex, sizeof(int), 1, fp);
            fwrite(&p->w, sizeof(int), 1, fp);
            p = p->nextarc;
        }
        int end_of_list = -1;
        fwrite(&end_of_list, sizeof(int), 1, fp);
    }
    fclose(fp);
    return OK;
}

status load(ALGraph &graph, char filename[]) {
    FILE *fp = fopen(filename, "rb+");
    if (!fp) {
        return ERROR;
    }
    fread(&graph.vexnum, sizeof(int), 1, fp);
    for (int i = 0; i < graph.vexnum; i++) {
        fread(&graph.vertices[i].data, sizeof(VertexType), 1, fp);
        int current_arcnum = 0, w = 0;
        fread(&current_arcnum, sizeof(int), 1, fp);
        fread(&w, sizeof(int), 1, fp);
        if (current_arcnum == -1) {
            graph.vertices[i].firstarc = NULL;
            continue;
        }
        graph.vertices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
        if (!graph.vertices[i].firstarc) {
            return ERROR;
        }
        graph.vertices[i].firstarc->adjvex = current_arcnum;
        graph.vertices[i].firstarc->w = w;
        graph.vertices[i].firstarc->nextarc = NULL;
        ArcNode *p = graph.vertices[i].firstarc, *next = NULL;
        for (fread(&current_arcnum, sizeof(int), 1, fp); current_arcnum != -1;
             fread(&current_arcnum, sizeof(int), 1, fp)) {
            fread(&w, sizeof(int), 1, fp);
            next = (ArcNode *)malloc(sizeof(ArcNode));
            next->adjvex = current_arcnum;
            next->w = w;
            next->nextarc = NULL;
            p->nextarc = next;
            p = next;
            next = NULL;
        }
    }
    fclose(fp);
    return OK;
}