/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <stdlib.h>

#include "algorithms.hpp"
#include "multi_list_management.h"
#include "sq_list.h"
#include "utils.h"

int main(void) {
    static LISTS lists = (LISTS){.listsize = 10};
    AddList(lists, "default_list");
    DestroyList(lists.elem[0].L);
    static LISTS::ListInfo *current_list = &lists.elem[0];
    strcpy(current_list->name, "default_list");
    int op = 1;
    while (op) {
        clean_terminal();
        if (lists.length == 0) {
            printf(
                "\n"
                "检测到多线性表里的线性表个数为 0 , 建议进入选项 14 "
                "添加线性表\n"
                "\n");
            getchar();
        }
        printf("\n现在的线性表是: %s, 状态为: %s\n", current_list->name,
               current_list->L.elem ? "已初始化" : "未初始化");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       7. LocateElem\n");
        printf("    	  2. DestroyList    8. PriorElem\n");
        printf("    	  3. ClearList      9. NextElem \n");
        printf("    	  4. ListEmpty      10. ListInsert\n");
        printf("    	  5. ListLength     11. ListDelete\n");
        printf("    	  6. GetElem        12. ListTraverse\n");
        printf("\n");
        printf("    	  13. 批量插入\n");
        printf("    	  14. 多线性表管理\n");
        printf("    	  15. 文件读写\n");
        printf("    	  16. 算法\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~16]:");
        scanf("%d", &op);
        switch (op) {
            case 1: {
                if (lists.length > 0 && InitList(current_list->L) == OK)
                    printf("\n线性表创建成功！\n");
                else
                    printf("\n线性表创建失败！\n");
            }
                getchar();
                getchar();
                break;
            case 2: {
                status s = DestroyList(current_list->L);
                if (s == OK && current_list->L.elem == NULL &&
                    current_list->L.length == 0) {
                    printf("\nDestroyList成功！\n");
                } else {
                    printf("\nDestroyList失败！\n");
                }
            }
                getchar();
                getchar();
                break;
            case 3: {
                status s = ClearList(current_list->L);
                if (s == OK && current_list->L.length == 0 &&
                    current_list->L.elem[current_list->L.length - 1] == 0) {
                    printf("\nClearList成功！\n");
                } else {
                    printf("\nClearList失败！\n");
                }
            }
                getchar();
                getchar();
                break;
            case 4: {
                status s = ListEmpty(current_list->L);
                if (s == TRUE) {
                    printf("\n线性表L事一个一个空表！\n");
                } else if (s == FALSE) {
                    printf("\n线性表L不事一个一个空表（悲\n");
                } else {
                    printf("\nINFEASIBLE\n");
                }
            }
                getchar();
                getchar();
                break;
            case 5: {
                int len = ListLength(current_list->L);
                if (len == INFEASIBLE) {
                    printf("\nINFEASIBLE!\n");
                } else {
                    printf("\n线性表的长度L为: %d\n", len);
                }
                getchar();
                getchar();
            } break;
            case 6: {
                int i = 0;
                printf("\n请输入要访问的位置 i (从 1 开始):\n");
                scanf("%d", &i);
                ElemType e = 0;
                status s = GetElem(current_list->L, i, e);
                if (s == INFEASIBLE) {
                    printf("\nINFEASIBLE!\n");
                } else if (s == ERROR) {
                    printf("\nERROR!\n");
                    printf("\n(有没有一种可能, i 超出了范围)\n");
                    printf("\n表L的长度是: %d\n", current_list->L.length);
                } else {
                    printf("\n第 i 位的数据为: %d\n", e);
                }
            }
                getchar();
                getchar();
                break;
            case 7: {
                printf("\n请输入待查找数据 e :\n");
                ElemType e = 0;
                scanf("%d", &e);
                int i = LocateElem(current_list->L, e);
                if (i == INFEASIBLE) {
                    printf("\nINFEASIBLE!\n");
                } else if (i == ERROR) {
                    printf("\n没有找到 e 捏\n");
                } else {
                    printf("\ne 的位置(从 1 开始)是: %d\n", i);
                }
            }
                getchar();
                getchar();
                break;
            case 8: {
                printf("\n请输入待查找数据 e :\n");
                ElemType e = 0, pre = 0;
                scanf("%d", &e);
                status s = PriorElem(current_list->L, e, pre);
                if (s == INFEASIBLE) {
                    printf("\nINFEASIBLE!\n");
                } else if (s == ERROR) {
                    printf("\n没有捏\n");
                } else {
                    printf("\ne 的前驱是: %d\n", pre);
                }
            }
                getchar();
                getchar();
                break;
            case 9: {
                printf("\n请输入待查找数据 e :\n");
                ElemType e = 0, next = 0;
                scanf("%d", &e);
                status s = NextElem(current_list->L, e, next);
                if (s == INFEASIBLE) {
                    printf("\nINFEASIBLE!\n");
                } else if (s == ERROR) {
                    printf("\n没有捏\n");
                } else {
                    printf("\ne 的后继是: %d\n", next);
                }
            }
                getchar();
                getchar();
                break;
            case 10: {
                ElemType e = 0;
                int i = 0;
                printf(
                    "\n请输入要插入的元素 e 和插入位置 i (从 1 开始), "
                    "以空白符分隔: \n");
                scanf("%d%d", &e, &i);
                status s = ListInsert(current_list->L, i, e);
                if (s == INFEASIBLE) {
                    printf("\nINFEASIBLE!\n");
                } else if (s == ERROR) {
                    printf("\nERROR!\n");
                    printf("\n(有没有一种可能, i 超出了范围)\n");
                    printf("\n表L的长度是: %d\n", current_list->L.length);
                } else {
                    printf("\n插入成功！\n");
                }
            }
                getchar();
                getchar();
                break;
            case 11: {
                ElemType e = 0;
                int i = 0;
                printf("\n请输入要删除的元素位置 i (从 1 开始): \n");
                scanf("%d", &i);
                status s = ListDelete(current_list->L, i, e);
                if (s == INFEASIBLE) {
                    printf("\nINFEASIBLE!\n");
                } else if (s == ERROR) {
                    printf("\nERROR!\n");
                    printf("\n(有没有一种可能, i 超出了范围)\n");
                } else {
                    printf("\n删除成功！删除的元素是: %d\n", e);
                }
            }
                getchar();
                getchar();
                break;
            case 12: {
                if (!ListTraverse(current_list->L)) printf("线性表是空表！\n");
            }
                getchar();
                getchar();
                break;
            case 13: {
                if (current_list->L.elem == NULL) {
                    printf("\nINFEASIBLE!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf(
                    "\n现在可以对线性表L从尾部批量插入元素。请输入待插入元素个"
                    "数 n:\n");
                int n = 0;
                scanf("%d", &n);
                printf("\n请输入元素: \n");
                status s = OK;
                for (int i = 1; i <= n; i++) {
                    ElemType e = 0;
                    scanf("%d", &e);
                    s = ListInsert(current_list->L, current_list->L.length + 1,
                                   e);
                    if (s != OK) {
                        printf("\n插入失败, 元素为: %d\n", e);
                    }
                }
                if (s == OK) {
                    printf("\n插入成功！现在列表为:\n");
                    ListTraverse(current_list->L);
                }
            }
                getchar();
                getchar();
                break;
            case 14: {
                int op_multilist = 1;
                while (op_multilist) {
                    clean_terminal();
                    printf("\n线性表管理\n");
                    printf(
                        "\n"
                        "现在你可以对多个线性表进行管理, "
                        "并切换主程序所访问的线性表\n"
                        "要注意, 你在\"线性表管理\"以外的地方进行的所有操作, "
                        "都会影响多线性表本身的数据\n"
                        "请谨慎操作\n"
                        "!!!!!!!!注意!!!!!!!!!\n"
                        "!!!!线性表不能重名!!!!!\n"
                        "\n");
                    printf(
                        "\n"
                        "现在的线性表有: "
                        "\n");
                    for (int i = 0; i < lists.length; i++) {
                        printf("%s", lists.elem[i].name);
                        if (&current_list->L == &lists.elem[i].L) {
                            printf("  *");
                        }
                        printf("\n");
                    }
                    printf("\n");

                    printf(
                        "                  <多线性表操作菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 添加线性表\n");
                    printf("    	  2. 删除线性表\n");
                    printf("    	  3. 查找线性表\n");
                    printf("    	  4. 切换线性表\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~4]:");
                    scanf("%d", &op_multilist);
                    switch (op_multilist) {
                        case 1: {
                            printf("\n请输入待添加线性表的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            status s = AddList(lists, name);
                            if (s == ERROR) {
                                printf("\n添加失败!\n");
                                printf("\n多线性表长度: %d\n", lists.length);
                            } else {
                                printf("\n添加成功!\n");
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            printf("\n请输入待删除线性表的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            if (!strcmp(name, current_list->name)) {
                                current_list = &lists.elem[0];
                                strcpy(current_list->name, lists.elem[0].name);
                            }
                            status pos_curr =
                                LocateList(lists, current_list->name);
                            status pos_to_be_deleted = LocateList(lists, name);
                            if (pos_to_be_deleted != -1 &&
                                pos_to_be_deleted < pos_curr) {
                                --current_list;
                            }
                            status s = RemoveList(lists, name);
                            if (s == ERROR) {
                                printf(
                                    "\n删除失败!多线性表长度为 0 "
                                    "或线性表未找到\n");
                                printf("\n多线性表长度: %d\n", lists.length);
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
                            int s = LocateList(lists, name);
                            if (s == ERROR) {
                                printf("\n查找失败!多线性表长度为 0\n");
                                printf("\n多线性表长度: %d\n", lists.length);
                            } else if (s == -1) {
                                printf("\n未找到!\n");
                            } else {
                                printf("\n线性表的位置为: %d\n", s);
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 4: {
                            printf("\n请输入线性表的名字: \n");
                            char name[30] = "";
                            scanf("%s", name);
                            int s = LocateList(lists, name);
                            if (s == ERROR) {
                                printf("\n切换失败!多线性表长度为 0\n");
                                printf("\n多线性表长度: %d\n", lists.length);
                            } else if (s == -1) {
                                printf("\n线性表不存在!\n");
                            } else {
                                printf("\n线性表的位置为: %d\n", s);
                                current_list = &lists.elem[s - 1];
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 0:
                            break;
                        default:
                            break;
                    }
                }
            }
                getchar();
                getchar();
                break;
            case 15: {
                int op_file_io = 1;
                while (op_file_io) {
                    clean_terminal();
                    printf("\n");
                    printf(
                        "                  <线性表文件操作菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 从文件将表初始化\n");
                    printf("    	  2. 从文件读入并覆盖原表\n");
                    printf("    	  3. 保存到文件\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~3]:");
                    scanf("%d", &op_file_io);
                    switch (op_file_io) {
                        case 1: {
                            printf("\n请输入完整文件名(二进制文件): \n");
                            char filename[30] = "";
                            scanf("%s", filename);
                            status s = LoadList(current_list->L, filename);
                            if (s == INFEASIBLE) {
                                printf("\n线性表已存在, 无法读入\n");
                            } else if (s == ERROR) {
                                printf("\n发生错误\n");
                            } else if (s == OK) {
                                printf("\n线性表读入成功\n");
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            SqList temp = (SqList){.elem = NULL};
                            printf("\n请输入完整文件名(二进制文件): \n");
                            char filename[30] = "";
                            scanf("%s", filename);
                            status s = LoadList(temp, filename);
                            if (s == ERROR) {
                                printf("\n发生错误\n");
                            } else if (s == OK) {
                                DestroyList(current_list->L);
                                current_list->L = temp;
                                printf("\n线性表读入成功\n");
                                ListTraverse(current_list->L);
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 3: {
                            printf("\n请输入完整文件名(二进制文件): \n");
                            char filename[30] = "";
                            scanf("%s", filename);
                            status s = SaveList(current_list->L, filename);
                            if (s == INFEASIBLE) {
                                printf("\n线性表为空, 无法保存\n");
                            } else if (s == ERROR) {
                                printf("\n发生错误\n");
                            } else {
                                printf("\n线性表保存成功\n");
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
            case 16: {
                int op_algo = 1;
                while (op_algo) {
                    clean_terminal();
                    printf("\n");
                    printf(
                        "                  <线性表算法菜单>                "
                        "\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    	  1. 求最大子段和\n");
                    printf("    	  2. 排序\n");
                    printf("    	  3. 求和为 k 的子段数\n");
                    printf("    	  0. Exit\n");
                    printf(
                        "-------------------------------------------------\n");
                    printf("    请选择你的操作[0~3]:");
                    scanf("%d", &op_algo);
                    switch (op_algo) {
                        case 1: {
                            ElemType res = max_partial_sum(current_list->L);
                            if (res == 0x7fffffff) {
                                printf("\n线性表为空\n");
                            } else {
                                printf("\n最大子段和: %d\n", res);
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 2: {
                            status s = sort_list(current_list->L);
                            if (s == INFEASIBLE) {
                                printf("\n线性表为空\n");
                            } else {
                                printf("\n排序成功!\n");
                                ListTraverse(current_list->L);
                            }
                        }
                            getchar();
                            getchar();
                            break;
                        case 3: {
                            printf("\n请输入 k:\n");
                            int k = 0;
                            scanf("%d", &k);
                            int res = k_subarray(current_list->L, k);
                            if (res == INFEASIBLE) {
                                printf("\n线性表为空\n");
                            } else {
                                printf("\n和为 k 的子段数: %d\n", res);
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
                for (int i = 0; i < lists.length; i++) {
                    DestroyList(lists.elem[i].L);
                }
            } break;
        }  // end of switch
    }      // end of while
    printf("欢迎下次再使用本系统！\n");
}  // end of main()