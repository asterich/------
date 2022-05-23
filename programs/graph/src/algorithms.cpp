#include "algorithms.h"

std::vector<int> VerticesSetLessThanK(ALGraph G, KeyType v, int k) {
    int _v = LocateVex(G, v);
    if (_v == -1) {
        return std::vector<int>{};
    }
    auto dis = dijkstra(G, _v);
    auto res_view =
        std::views::iota(0, G.vexnum) |
        std::views::filter([dis, k](int u) -> bool { return dis[u] < k; }) |
        std::views::transform([G](int u) { return G.vertices[u].data.key; });
    std::vector<int> res(res_view.begin(), res_view.end());
    return res;
}

int ShortestPathLength(ALGraph G, KeyType v, KeyType w) {
    int _v = LocateVex(G, v);
    if (_v == -1) {
        return -1;  // can't find
    }
    int _w = LocateVex(G, w);
    if (_w == -1) {
        return -1;  // can't find
    }
    auto dis = dijkstra(G, _v);
    return dis[_w];
}

int ConnectedComponentsNums(ALGraph G) { return connected_components_cnt(G); }