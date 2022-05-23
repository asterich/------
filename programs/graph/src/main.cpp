#include <iostream>
#include <vector>

#include "algorithms.h"
#include "graph.h"
#include "multi_graph_management.h"
#include "utils.h"

using namespace std;

#define MAX_VERTEX_BUF_NUM 100
#define MAX_EDGE_BUF_NUM 4950

int main() {
    static MultiGraphTable graph_table = (MultiGraphTable){.listsize = 10};
    AddGraph(graph_table, "default_graph");
    static MultiGraphTable::GraphInfo *current_graph = &graph_table.elem[0];
    int op = 1;
    while (op) {
        clean_terminal();
        if (graph_table.length == 0) {
            printf(
                "\n"
                "检测到多图管理表里的图个数为 0 , 建议进入选项 14 "
                "添加图\n"
                "\n");
            getchar();
            getchar();
        }
        printf("\n现在的图是: %s, 状态为: %s\n", current_graph->name,
               current_graph->g_status == GraphStatus::CREATED ? "已创建"
                                                               : "未创建");
        printf("\n\n");
        printf(R"(
-----------------图------------------

1. 创建图
2. 销毁图

3. 查找顶点
4. 给顶点赋值
5. 添加顶点
6. 删除顶点

7. 查找某顶点邻接表的第一个顶点(FirstAdjVex)
8. 查找某顶点邻接表某节点的下一个(NextAdjVex)

9. 插入边
10. 删除边

11. 遍历...

12. 文件操作...

13. 多图管理...

14. 算法...

0. 退出
----------------------------------------
请选择你的操作[0~14]:)");
        scanf("%d", &op);
        switch (op) {
            case 1: {
                if (current_graph->g_status == GraphStatus::CREATED) {
                    printf("\n图已经创建");
                    goto err_1;
                }
                printf("\n请输入顶点数 n 和边数 e:\n");
                int n, e;
                scanf("%d%d", &n, &e);
                printf("\n请输入所有顶点(key, others):\n");
                VertexType *vertices = (VertexType *)malloc(MAX_VERTEX_BUF_NUM *
                                                            sizeof(VertexType));
                for (int i = 0; i < n; i++) {
                    scanf("%d %s", &vertices[i].key, vertices[i].others);
                }
                vertices[n] = VertexType{.key = -1};
                printf("\n请输入所有边(u, v, w):\n");
                KeyType(*edges)[3] = (KeyType(*)[3])malloc(MAX_EDGE_BUF_NUM *
                                                           sizeof(KeyType[3]));
                for (int i = 0; i < e; i++) {
                    scanf("%d%d%d", &edges[i][0], &edges[i][1], &edges[i][2]);
                }
                edges[e][0] = edges[e][1] = edges[e][2] = -1;
                status s = CreateGraph(current_graph->G, vertices, edges);
                if (s == ERROR) {
                    printf("\n创建图错误\n");
                } else {
                    current_graph->g_status = GraphStatus::CREATED;
                }
                free(vertices);
                free(edges);
            }
            err_1:
                getchar();
                getchar();
                break;
            case 2: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_2;
                }
                status s = DestroyGraph(current_graph->G);
                if (s == ERROR) {
                    printf("\n销毁图错误\n");
                } else {
                    current_graph->g_status = GraphStatus::NOT_CREATED;
                }
            }
            err_2:
                getchar();
                getchar();
                break;
            case 3: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_3;
                }
                printf("\n请输入待查找顶点 u:\n");
                int u;
                scanf("%d", &u);
                int s = LocateVex(current_graph->G, u);
                if (s == -1) {
                    printf("\n没找到\n");
                } else {
                    printf("\n顶点位置是: %d\n", s);
                }
            }
            err_3:
                getchar();
                getchar();
                break;
            case 4: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_4;
                }
                printf("\n请输入要赋值的顶点 u:\n");
                int u;
                scanf("%d", &u);
                printf("\n请输入要给顶点赋的值(key, others):\n");
                VertexType val;
                scanf("%d %s", &val.key, val.others);
                status s = PutVex(current_graph->G, u, val);
                if (s == ERROR) {
                    printf("\n赋值失败, 说不定是没找到顶点\n");
                } else {
                    printf("\n赋值成功\n");
                }
            }
            err_4:
                getchar();
                getchar();
                break;
            case 5: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_5;
                }
                printf("\n请输入新顶点的值(key, others):\n");
                VertexType val;
                scanf("%d %s", &val.key, val.others);
                status s = InsertVex(current_graph->G, val);
                if (s == ERROR) {
                    printf("\n插入失败\n");
                } else {
                    printf("\n插入成功\n");
                }
            }
            err_5:
                getchar();
                getchar();
                break;
            case 6: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_6;
                }
                printf("\n请输入待删除顶点的 key:\n");
                KeyType u;
                scanf("%d", &u);
                status s = DeleteVex(current_graph->G, u);
                if (s == ERROR) {
                    printf("\n删除失败\n");
                } else {
                    printf("\n删除成功\n");
                }
            }
            err_6:
                getchar();
                getchar();
                break;
            case 7: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_7;
                }
                printf("\n请输入顶点 u:\n");
                int u;
                scanf("%d", &u);
                auto s = FirstAdjVex(current_graph->G, u);
                if (s == -1) {
                    printf("\n没找到捏\n");
                } else {
                    printf("\n要找的顶点是: %d\n", s);
                }
            }
            err_7:
                getchar();
                getchar();
                break;
            case 8: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_8;
                }
                printf("\n请输入顶点 u, v:\n");
                int u, v;
                scanf("%d%d", &u, &v);
                auto s = NextAdjVex(current_graph->G, u, v);
                if (s == -1) {
                    printf("\n没找到捏\n");
                } else {
                    printf("\n要找的顶点是: %d\n", s);
                }
            }
            err_8:
                getchar();
                getchar();
                break;
            case 9: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_9;
                }
                printf("\n请输入顶点 u, v:\n");
                int u, v;
                scanf("%d%d", &u, &v);
                printf("\n请输入边的权重 w:\n");
                int w;
                scanf("%d", &w);
                status s = InsertArc(current_graph->G, u, v, w);
                if (s != OK) {
                    printf("\n似乎出了点问题, 有可能是已经有了一条边\n");
                } else {
                    printf("\n插入成功\n");
                }
            }
            err_9:
                getchar();
                getchar();
                break;
            case 10: {
                if (current_graph->g_status == GraphStatus::NOT_CREATED) {
                    printf("\n图还没创建");
                    goto err_10;
                }
                printf("\n请输入顶点 u, v:\n");
                int u, v;
                scanf("%d%d", &u, &v);
                status s = DeleteArc(current_graph->G, u, v);
                if (s != OK) {
                    printf("\n似乎出了点问题, 可能是没有这条边\n");
                } else {
                    printf("\n删除成功\n");
                }
            }
            err_10:
                getchar();
                getchar();
                break;
            case 11: {
                int op_trav = 1;
                while (op_trav) {
                    clean_terminal();
                    printf("\n");
                    printf(
                        "                  <图遍历菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. DFS\n");
                    printf("    	  2. BFS\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~2]:");
                    scanf("%d", &op_trav);
                    switch (op_trav) {
                        case 1: {
                            printf("\nDFS遍历为:\n");
                            DFSTraverse(current_graph->G,
                                        [](VertexType u) -> void {
                                            printf("%d %s ", u.key, u.others);
                                        });
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            printf("\nBFS遍历为:\n");
                            BFSTraverse(current_graph->G,
                                        [](VertexType u) -> void {
                                            printf("%d %s ", u.key, u.others);
                                        });
                        }
                            getchar();
                            getchar();
                            break;
                        case 0:
                            break;
                    }
                }
            }
                getchar();
                getchar();
                break;
            case 12: {
                int op_file = 1;
                while (op_file) {
                    clean_terminal();
                    printf("\n");
                    printf(
                        "                  <图文件菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 保存到文件\n");
                    printf("    	  2. 从文件加载\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~2]:\n");
                    scanf("%d", &op_file);
                    switch (op_file) {
                        case 1: {
                            if (current_graph->g_status ==
                                GraphStatus::NOT_CREATED) {
                                printf("\n图还没有创建捏\n");
                                goto err_file_1;
                            }
                            printf("\n请输入要保存的文件名:\n");
                            char filename[100];
                            scanf("%s", filename);
                            status s = SaveGraph(current_graph->G, filename);
                            if (s == ERROR) {
                                printf("\n发生错误\n");
                            } else {
                                printf("\n保存成功\n");
                            }
                        }
                        err_file_1:
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            if (current_graph->g_status ==
                                GraphStatus::CREATED) {
                                printf("\n已经有图了捏\n");
                                goto err_file_2;
                            }
                            printf("\n请输入要加载的文件名:\n");
                            char filename[100];
                            scanf("%s", filename);
                            status s = LoadGraph(current_graph->G, filename);
                            if (s == ERROR) {
                                printf("\n发生错误\n");
                            } else {
                                printf("\n加载成功\n");
                                current_graph->g_status = GraphStatus::CREATED;
                            }
                        }
                        err_file_2:
                            getchar();
                            getchar();
                            break;
                        case 0:
                            break;
                    }
                }
            }
                getchar();
                getchar();
                break;
            case 13: {
                int op_multi = 1;
                while (op_multi) {
                    clean_terminal();
                    printf(
                        "\n"
                        "现在的图有: "
                        "\n");
                    for (int i = 0; i < graph_table.length; i++) {
                        printf("%s", graph_table.elem[i].name);
                        if (current_graph == &graph_table.elem[i]) {
                            printf("  *");
                        }
                        printf("\n");
                    }
                    printf("\n");
                    printf("\n");
                    printf(
                        "                  <多图管理菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 添加图\n");
                    printf("    	  2. 删除图\n");
                    printf("    	  3. 查找图\n");
                    printf("    	  4. 切换图\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~4]:");
                    scanf("%d", &op_multi);
                    switch (op_multi) {
                        case 1: {
                            printf("\n请输入待添加图的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            status s = AddGraph(graph_table, name);
                            if (s == ERROR) {
                                printf("\n添加失败!\n");
                                printf("\n多图管理表长度: %d\n",
                                       graph_table.length);
                            } else {
                                printf("\n添加成功!\n");
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            printf("\n请输入待删除图的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            if (!strcmp(name, current_graph->name)) {
                                current_graph = &graph_table.elem[0];
                                // strcpy(current_graph->name,
                                // lists.elem[0].name);
                            }
                            status s = RemoveGraph(graph_table, name);
                            if (s == ERROR) {
                                printf(
                                    "\n删除失败!图管理表长度为 0 "
                                    "或图未找到\n");
                                printf("\n图管理表长度: %d\n",
                                       graph_table.length);
                            } else {
                                printf("\n删除成功!\n");
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 3: {
                            printf("\n请输入图管理表的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            int s = LocateGraph(graph_table, name);
                            if (s == ERROR) {
                                printf("\n查找失败!图管理表长度为 0\n");
                                printf("\n图管理表长度: %d\n",
                                       graph_table.length);
                            } else if (s == -1) {
                                printf("\n未找到!\n");
                            } else {
                                printf("\n图的位置为: %d\n", s);
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 4: {
                            printf("\n请输入图的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            int s = LocateGraph(graph_table, name);
                            if (s == ERROR) {
                                printf("\n切换失败!图管理表长度为 0\n");
                                printf("\n图管理表长度: %d\n",
                                       graph_table.length);
                            } else if (s == -1) {
                                printf("\n图不存在!\n");
                            } else {
                                printf("\n图的位置为: %d\n", s);
                                current_graph = &graph_table.elem[s - 1];
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 0:
                            break;
                    }
                }
            }
                getchar();
                getchar();
                break;
            case 14: {
                int op_algo = 1;
                while (op_algo) {
                    clean_terminal();
                    printf("\n");
                    printf(
                        "                  <图算法菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 与某一点距离不超过k的点集\n");
                    printf("    	  2. 最短路\n");
                    printf("    	  3. 连通分量(无向图)\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~3]:");
                    scanf("%d", &op_algo);
                    switch (op_algo) {
                        case 1: {
                            printf("请输入待求顶点 u 的 key:");
                            int u;
                            scanf("%d", &u);
                            printf("请输入k:");
                            int k;
                            scanf("%d", &k);
                            auto vertices =
                                VerticesSetLessThanK(current_graph->G, u, k);
                            printf("顶点集为:\n");
                            for (auto i : vertices) {
                                printf("%d ", i);
                            }
                            printf("\n");
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            printf("请输入待求顶点 u、v 的 key:");
                            int u, v;
                            scanf("%d%d", &u, &v);
                            int i = ShortestPathLength(current_graph->G, u, v);
                            printf("最短路长度: %d\n", i);
                        }
                            getchar();
                            getchar();
                            break;
                        case 3: {
                            int i = ConnectedComponentsNums(current_graph->G);
                            printf("连通分量的个数为: %d\n", i);
                        }
                            getchar();
                            getchar();
                            break;
                        case 0:
                            break;
                    }
                }
            }
                getchar();
                getchar();
                break;
        }
    }
    return 0;
}