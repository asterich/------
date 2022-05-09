#include "algorithms_impl.h"

struct dis_vex_pair {
    int dis;
    int u;
    bool operator>(const dis_vex_pair& rhs) const {
        return this->dis > rhs.dis;
    }
};

/**
 * @brief Dijkstra algorithm. Returns the distance vector of %u.
 *
 * @param G
 * @param u The node number in the array
 * @return std::vector<int> The distance vector of %u
 */
std::vector<int> dijkstra(ALGraph G, int u) {
    std::vector<int> dis(505, INT32_MAX);
    std::deque<bool> visited(505, false);
    std::priority_queue<dis_vex_pair, std::vector<dis_vex_pair>,
                        std::greater<dis_vex_pair>>
        dis_pq;
    dis[u] = 0;
    dis_pq.push(dis_vex_pair{0, u});
    while (!dis_pq.empty()) {
        auto uw_pair = dis_pq.top();
        dis_pq.pop();
        if (visited[uw_pair.u]) {
            continue;
        }
        visited[uw_pair.u] = true;
        auto& current_node = G.vertices[uw_pair.u];
        auto p = current_node.firstarc;
        while (p) {
            int curr_u = uw_pair.u, v = p->adjvex, w = p->w;
            if (dis[v] > dis[curr_u] + w) {
                dis[v] = dis[curr_u] + w;
                dis_pq.push(dis_vex_pair{dis[v], v});
            }
            p = p->nextarc;
        }
    }
    return dis;
}

/**
 * @brief Returns the number of strongly-connected components in a directed
 * graph.
 * TODO
 *
 * @param G
 * @return int
 */
int tarjan(ALGraph G) {
    // TODO
    return -1;
}

/**
 * @brief Returns the number of connected components in a undirected graph.
 *
 * @param G
 * @return int
 */
int connected_components_cnt(ALGraph G) {
    int res = 0;
    int visited_node[MAX_VERTEX_NUM + 1] = {};
    std::stack<KeyType> node_stack;
    int visited_node_cnt = 0;

    if (G.vexnum <= 0) {
        return 0;
    }

    while (visited_node_cnt < G.vexnum) {
        while (!node_stack.empty()) {
            KeyType current_node = node_stack.top();
            node_stack.pop();
            if (visited_node[current_node]) {
                continue;
            }
            visited_node[current_node] = 1;
            ++visited_node_cnt;
            const ArcNode* p = G.vertices[current_node].firstarc;
            while (p) {
                if (!visited_node[p->adjvex]) {
                    node_stack.push(p->adjvex);
                }
                p = p->nextarc;
            }
        }
        for (int i = 0; i < G.vexnum; ++i) {
            if (!visited_node[i]) {
                node_stack.push(i);
                ++res;
                break;
            }
        }
    }
    return res;
}