/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"
#include "multi_tree_management.h"
#include "utils.h"

#define MAX_ELEMENT_BUF_SIZE 1024

int main(void) {
    static MultiTreeTable tree_table = (MultiTreeTable){.listsize = 10};
    AddTree(tree_table, "default_tree");
    static MultiTreeTable::TreeInfo *current_tree = &tree_table.elem[0];
    int op = 1;
    while (op) {
        clean_terminal();
        if (tree_table.length == 0) {
            printf(
                "\n"
                "检测到二叉树表里的二叉树个数为 0 , 建议进入选项 14 "
                "添加二叉树\n"
                "\n");
            getchar();
            getchar();
        }
        printf("\n现在的二叉树是: %s, 状态为: %s\n", current_tree->name,
               current_tree->L ? "已初始化" : "未初始化");
        printf("\n\n");
        printf(R"(
-----------------二叉树------------------

1. 创建二叉树(从带 NULL 节点的先序遍历)
2. 清空二叉树

3. 求树高
4. 查找树中节点
5. 查找树中节点并赋值
6. 获取节点的兄弟

7. 插入节点
8. 删除节点

9. 遍历...

10. 文件操作...

11. 算法...

12. 多树管理...

0. 退出
----------------------------------------
请输入操作[0~12]:
)");
        scanf("%d", &op);
        switch (op) {
            case 1: {
                printf("\n请输入树的先序遍历(含NULL节点, 以-1结束):\n");
                TElemType *buf = (TElemType *)malloc(
                    (MAX_ELEMENT_BUF_SIZE + 1) * sizeof(TElemType));
                int t = 0;
                while (t < MAX_ELEMENT_BUF_SIZE) {
                    TElemType elem;
                    scanf("%d %s", &elem.key, elem.others);
                    memcpy(&buf[t++], &elem, sizeof(TElemType));
                    if (elem.key == -1) {
                        break;
                    }
                }
                if (t >= MAX_ELEMENT_BUF_SIZE) {
                    printf("\n元素太多力\n");
                } else {
                    status s = CreateBiTree(current_tree->L, buf);
                    if (s == ERROR) {
                        printf("\n有重复的key\n");
                    } else if (s == INFEASIBLE) {
                        printf("INFEASIBLE");
                    } else {
                        printf("\n创建成功\n");
                        printf("\n树的先序遍历为:\n");
                        PreOrderTraverse(current_tree->L, [](BiTree T) -> void {
                            printf("%d %s ", T->data.key, T->data.others);
                        });
                        printf("\n树的中序遍历为:\n");
                        InOrderTraverse(current_tree->L, [](BiTree T) -> void {
                            printf("%d %s ", T->data.key, T->data.others);
                        });
                    }
                }
                free(buf);
            }
                getchar();
                getchar();
                break;
            case 2: {
                status s = ClearBiTree(current_tree->L);
                if (s == OK) {
                    printf("\n清除二叉树成功\n");
                } else if (s == INFEASIBLE) {
                    printf("\nINFEASIBLE\n");
                }
            }
                getchar();
                getchar();
                break;
            case 3: {
                printf("\n树的深度是: %d\n", BiTreeDepth(current_tree->L));
            }
                getchar();
                getchar();
                break;
            case 4: {
                printf("\n请输入待查找节点的key:\n");
                KeyType k;
                scanf("%d", &k);
                const BiTNode *node = LocateNode(current_tree->L, k);
                if (!node) {
                    printf("\n没找到捏\n");
                } else {
                    printf("\n找到力! key事: %d, others事: %s\n",
                           node->data.key, node->data.others);
                }
            }
                getchar();
                getchar();
                break;
            case 5: {
                printf("\n请输入待赋值节点的key:\n");
                KeyType k;
                scanf("%d", &k);
                printf("\n请输入要赋的值(key, others):\n");
                TElemType elem;
                scanf("%d %s", &elem.key, elem.others);
                status s = Assign(current_tree->L, k, elem);
                if (s == ERROR) {
                    printf("\n没找到节点, 或者key发生重复\n");
                } else {
                    printf("\n赋值成功\n");
                }
            }
                getchar();
                getchar();
                break;
            case 6: {
                printf("\n请输入待查找节点的key:\n");
                KeyType k;
                scanf("%d", &k);
                const BiTNode *node = GetSibling(current_tree->L, k);
                if (!node) {
                    printf("\n节点不存在, 或者兄弟节点事NULL\n");
                } else {
                    printf("\n找到力! 兄弟节点的key事: %d, others事: %s\n",
                           node->data.key, node->data.others);
                }
            }
                getchar();
                getchar();
                break;
            case 7: {
                printf("\n请输入待插入节点的值(key, others):\n");
                TElemType elem;
                scanf("%d %s", &elem.key, elem.others);
                printf("\n请输入插入位置的key:\n");
                KeyType k;
                scanf("%d", &k);
                printf(
                    "\n事左节点, 右节点还是根节点?\n"
                    "左节点扣0, 右节点扣1, 根节点扣-1:\n");
                int lr_flg;
                scanf("%d", &lr_flg);
                while (lr_flg < -1 || lr_flg > 1) {
                    printf(
                        "\n输错力\n"
                        "请再输一遍\n");
                    scanf("%d", &lr_flg);
                }
                status s = InsertNode(current_tree->L, k, lr_flg, elem);
                if (s == ERROR) {
                    printf("\n插入位置不存在, 或key有重复\n");
                } else {
                    printf("\n插入成功\n");
                }
            }
                getchar();
                getchar();
                break;
            case 8: {
                printf("\n请输入待删除节点的key:\n");
                KeyType k;
                scanf("%d", &k);
                status s = DeleteNode(current_tree->L, k);
                if (s == ERROR) {
                    printf("\n没找到捏\n");
                } else {
                    printf("\n删除成功\n");
                }
            }
                getchar();
                getchar();
                break;
            case 9: {
                int op_trav = 1;
                while (op_trav) {
                    clean_terminal();
                    printf("\n");
                    printf(
                        "                  <二叉树遍历菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 先序遍历\n");
                    printf("    	  2. 中序遍历\n");
                    printf("    	  3. 后序遍历\n");
                    printf("    	  4. 按层遍历\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~4]:");
                    scanf("%d", &op_trav);
                    switch (op_trav) {
                        case 1: {
                            printf("\n树的先序遍历为:\n");
                            PreOrderTraverse(current_tree->L,
                                             [](BiTree T) -> void {
                                                 printf("%d %s ", T->data.key,
                                                        T->data.others);
                                             });
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            printf("\n树的中序遍历为:\n");
                            InOrderTraverse(current_tree->L,
                                            [](BiTree T) -> void {
                                                printf("%d %s ", T->data.key,
                                                       T->data.others);
                                            });
                        }
                            getchar();
                            getchar();
                            break;
                        case 3: {
                            printf("\n树的后序遍历为:\n");
                            PostOrderTraverse(current_tree->L,
                                              [](BiTree T) -> void {
                                                  printf("%d %s ", T->data.key,
                                                         T->data.others);
                                              });
                        }
                            getchar();
                            getchar();
                            break;
                        case 4: {
                            printf("\n树的按层遍历为:\n");
                            LevelOrderTraverse(current_tree->L,
                                               [](BiTree T) -> void {
                                                   printf("%d %s ", T->data.key,
                                                          T->data.others);
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
            case 10: {
                int op_file = 1;
                while (op_file) {
                    clean_terminal();
                    printf("\n");
                    printf(
                        "                  <二叉树文件菜单>                "
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
                            printf("\n请输入要保存的文件名:\n");
                            char filename[100];
                            scanf("%s", filename);
                            status s = SaveBiTree(current_tree->L, filename);
                            if (s == ERROR) {
                                printf("\n发生错误\n");
                            } else {
                                printf("\n保存成功\n");
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            printf("\n请输入要加载的文件名:\n");
                            char filename[100];
                            scanf("%s", filename);
                            status s = LoadBiTree(current_tree->L, filename);
                            if (s == ERROR) {
                                printf("\n发生错误\n");
                            } else {
                                printf("\n加载成功\n");
                                printf("\n树的先序遍历为:\n");
                                PreOrderTraverse(
                                    current_tree->L, [](BiTree T) -> void {
                                        printf("%d %s ", T->data.key,
                                               T->data.others);
                                    });
                                printf("\n树的中序遍历为:\n");
                                InOrderTraverse(
                                    current_tree->L, [](BiTree T) -> void {
                                        printf("%d %s ", T->data.key,
                                               T->data.others);
                                    });
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 0: {
                        }
                            getchar();
                            getchar();
                            break;
                    }
                }
            }
                getchar();
                getchar();
                break;
            case 11: {
                int op_algo = 1;
                while (op_algo) {
                    clean_terminal();
                    printf("\n");
                    printf(
                        "                  <二叉树算法菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 二叉树翻转\n");
                    printf("    	  2. 根节点到叶子节点的最大路径和\n");
                    printf("    	  3. 最近公共祖先\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~3]:");
                    scanf("%d", &op_algo);
                    switch (op_algo) {
                        case 1: {
                            status s = InvertTree(current_tree->L);
                            if (s == ERROR) {
                            } else {
                                printf("\n翻转成功\n");
                                printf("\n树的先序遍历为:\n");
                                PreOrderTraverse(
                                    current_tree->L, [](BiTree T) -> void {
                                        printf("%d %s ", T->data.key,
                                               T->data.others);
                                    });
                                printf("\n树的中序遍历为:\n");
                                InOrderTraverse(
                                    current_tree->L, [](BiTree T) -> void {
                                        printf("%d %s ", T->data.key,
                                               T->data.others);
                                    });
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            int s = MaxPathSum(current_tree->L);
                            printf("\n最大路径和: %d\n", s);
                        }
                            getchar();
                            getchar();
                            break;
                        case 3: {
                            printf("\n请输入两个节点的key:\n");
                            int k[2];
                            BiTNode *nodes[2] = {NULL, NULL};
                            scanf("%d%d", k, k + 1);
                            for (int i = 0; i < 2; i++) {
                                nodes[i] = LocateNode(current_tree->L, k[i]);
                                if (!nodes[i]) {
                                    printf("找不到节点: %d\n", k[i]);
                                    goto end_11_3;
                                }
                            }
                            BiTNode *res = LowestCommonAncestor(
                                current_tree->L, nodes[0], nodes[1]);
                            if (res) {
                                printf(
                                    "\n最近公共祖先的key事: %d, others事: %s\n",
                                    res->data.key, res->data.others);
                            }
                        }
                        end_11_3:
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
                int op_multi = 1;
                while (op_multi) {
                    clean_terminal();
                    printf(
                        "\n"
                        "现在的二叉树有: "
                        "\n");
                    for (int i = 0; i < tree_table.length; i++) {
                        printf("%s", tree_table.elem[i].name);
                        if (current_tree == &tree_table.elem[i]) {
                            printf("  *");
                        }
                        printf("\n");
                    }
                    printf("\n");
                    printf("\n");
                    printf(
                        "                  <多二叉树菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 添加二叉树\n");
                    printf("    	  2. 删除二叉树\n");
                    printf("    	  3. 查找二叉树\n");
                    printf("    	  4. 切换二叉树\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~4]:");
                    scanf("%d", &op_multi);
                    switch (op_multi) {
                        case 1: {
                            printf("\n请输入待添加二叉树的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            status s = AddTree(tree_table, name);
                            if (s == ERROR) {
                                printf("\n添加失败!\n");
                                printf("\n多线性表长度: %d\n",
                                       tree_table.length);
                            } else {
                                printf("\n添加成功!\n");
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            printf("\n请输入待删除二叉树的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            if (!strcmp(name, current_tree->name)) {
                                current_tree = &tree_table.elem[0];
                                // strcpy(current_tree->name,
                                // lists.elem[0].name);
                            }
                            status s = RemoveTree(tree_table, name);
                            if (s == ERROR) {
                                printf(
                                    "\n删除失败!二叉树表长度为 0 "
                                    "或线性表未找到\n");
                                printf("\n二叉树表长度: %d\n",
                                       tree_table.length);
                            } else {
                                printf("\n删除成功!\n");
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 3: {
                            printf("\n请输入线性表的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            int s = LocateTree(tree_table, name);
                            if (s == ERROR) {
                                printf("\n查找失败!二叉树表长度为 0\n");
                                printf("\n二叉树表长度: %d\n",
                                       tree_table.length);
                            } else if (s == -1) {
                                printf("\n未找到!\n");
                            } else {
                                printf("\n二叉树的位置为: %d\n", s);
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 4: {
                            printf("\n请输入二叉树的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            int s = LocateTree(tree_table, name);
                            if (s == ERROR) {
                                printf("\n切换失败!二叉树表长度为 0\n");
                                printf("\n二叉树表长度: %d\n",
                                       tree_table.length);
                            } else if (s == -1) {
                                printf("\n二叉树不存在!\n");
                            } else {
                                printf("\n二叉树的位置为: %d\n", s);
                                current_tree = &tree_table.elem[s - 1];
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
            case 0: {
                for (int i = 0; i < tree_table.length; i++) {
                    ClearBiTree(tree_table.elem[i].L);
                }
            } break;
        }  // end of switch
    }      // end of while
    printf("本系统润了\n");
    return 0;
}  // end of main()
