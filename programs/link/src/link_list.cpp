#include "link_list.h"

/**
 * @brief Initialize a link list.
 *
 * @param L Link list
 * @return status
 */
status InitList(LinkList &L) {
    if (L != NULL) {
        return INFEASIBLE;
    }

    LNode *head = (LNode *)malloc(sizeof(LNode));
    if (head == NULL) {
        return ERROR;
    }

    head->data = 0;
    head->next = NULL;
    L = head;
    return OK;
}

/**
 * @brief Destroy a link list.
 *
 * @param L List
 * @return status
 */
status DestroyList(LinkList &L) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }
    LNode *p = L;
    while (p != NULL) {
        LNode *current = p;
        p = p->next;
        free(current);
    }
    L = NULL;
    return OK;

    /********** End **********/
}

/**
 * @brief Clear a link list.
 *
 * @param L
 * @return status
 */
status ClearList(LinkList &L) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    LNode *p = L;
    if (p->next == NULL) {
        return OK;
    }
    p = p->next;
    while (p != NULL) {
        LNode *current = p;
        p = p->next;
        free(current);
    }
    L->next = NULL;
    return OK;

    /********** End **********/
}

/**
 * @brief Check if a link list is empty.
 *
 * @param L
 * @return status
 */
status ListEmpty(LinkList L) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }
    if (L->next == NULL) {
        return TRUE;
    }
    return FALSE;
    /********** End **********/
}

/**
 * @brief Return the length of a link list.
 *
 * @param L
 * @return int
 */
int ListLength(LinkList L)
// 如果链表L存在，返回链表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    int len = 0;
    LNode *p = L->next;
    while (p != NULL) {
        ++len;
        p = p->next;
    }

    return len;

    /********** End **********/
}

/**
 * @brief Get the Elem object at position %i from the given link list and assign
 * to %e.
 *
 * @param L
 * @param i
 * @param e
 * @return status
 */
status GetElem(LinkList L, int i, ElemType &e)
// 如果链表L存在，获取链表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果链表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    int len = 0;
    LNode *p = L->next;
    while (p != NULL) {
        ++len;
        if (len == i) {
            e = p->data;
            return OK;
        }
        p = p->next;
    }

    if (i < 1 || i > len) {
        return ERROR;
    }

    return ERROR;

    /********** End **********/
}

/**
 * @brief Return the position of the given element %e in link list %L, if
 * exists.
 *
 * @param L
 * @param e
 * @return status
 */
status LocateElem(LinkList L, ElemType e)
// 如果链表L存在，查找元素e在链表L中的位置序号；如果e不存在，返回ERROR；当链表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    int len = 0;
    LNode *p = L->next;
    while (p != NULL) {
        ++len;
        if (p->data == e) {
            return len;
        }
        p = p->next;
    }

    return ERROR;

    /********** End **********/
}

/**
 * @brief Return the previous element of the given element %e in link list %L
 * if exists, and assign to %pre.
 *
 * @param L
 * @param e
 * @param pre
 * @return status
 */
status PriorElem(LinkList L, ElemType e, ElemType &pre)
// 如果链表L存在，获取链表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果链表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    if (L->next == NULL) {
        return ERROR;
    }

    LNode *p = L->next;
    while (p->next != NULL) {
        if (p->next != NULL) {
            if (p->next->data == e) {
                pre = p->data;
                return OK;
            }
        }
        p = p->next;
    }
    return ERROR;
    /********** End **********/
}

/**
 * @brief Return the next element of the given element %e in link list %L
 * if exists, and assign to %next.
 *
 * @param L
 * @param e
 * @param next
 * @return status
 */
status NextElem(LinkList L, ElemType e, ElemType &next)
// 如果链表L存在，获取链表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果链表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    if (L->next == NULL) {
        return ERROR;
    }

    LNode *p = L->next;
    while (p->next != NULL) {
        if (p->next != NULL) {
            if (p->data == e) {
                next = p->next->data;
                return OK;
            }
        }
        p = p->next;
    }
    return ERROR;

    /********** End **********/
}

/**
 * @brief Insert an element to a link list at the given position %i.
 *
 * @param L
 * @param i
 * @param e
 * @return status
 */
status ListInsert(LinkList &L, int i, ElemType e)
// 如果链表L存在，将元素e插入到链表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果链表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    if (i < 1 || i > ListLength(L) + 1) {
        return ERROR;
    }

    int pos = 0;
    LNode *p = L->next, *prev = L;
    while (p != NULL) {
        ++pos;
        if (pos == i) {
            break;
        }
        prev = p;
        p = p->next;
    }

    LNode *new_node = (LNode *)malloc(sizeof(ElemType));
    new_node->data = e;
    if (new_node == NULL) {
        return ERROR;
    }
    prev->next = new_node;
    new_node->next = p;
    return OK;

    /********** End **********/
}

/**
 * @brief Delete the element at the position %i in a link list.
 *
 * @param L
 * @param i
 * @param e
 * @return status
 */
status ListDelete(LinkList &L, int i, ElemType &e)
// 如果链表L存在，删除链表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果链表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    if (i < 1 || i > ListLength(L)) {
        return ERROR;
    }

    int pos = 0;
    LNode *p = L->next, *prev = L;
    while (p != NULL) {
        ++pos;
        if (pos == i) {
            break;
        }
        prev = p;
        p = p->next;
    }

    e = p->data;
    prev->next = p->next;
    free(p);
    return OK;

    /********** End **********/
}

/**
 * @brief Traverse a list.
 *
 * @param L
 * @return status
 */
status ListTraverse(LinkList L)
// 如果链表L存在，依次显示链表中的元素，每个元素间空一格，返回OK；如果链表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    LNode *p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }

    return OK;

    /********** End **********/
}

/**
 * @brief Save a list to the file with name %FileName.
 *
 * @param L
 * @param FileName
 * @return status
 */
status SaveList(LinkList L, char FileName[])
// 如果链表L存在，将链表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (L == NULL) {
        return INFEASIBLE;
    }

    FILE *fp = fopen(FileName, "wa+");
    if (fp == NULL) {
        return ERROR;
    }

    LNode *p = L->next;
    while (p != NULL) {
        fwrite(&p->data, sizeof(ElemType), 1, fp);
        p = p->next;
    }

    fclose(fp);
    return OK;
    /********** End 1 **********/
}

/**
 * @brief Load data from the file with name %FileName to an uninitalized list.
 *
 * @param L
 * @param FileName
 * @return status
 */
status LoadList(LinkList &L, char FileName[])
// 如果链表L不存在，将FileName文件中的数据读入到链表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if (L != NULL) {
        return INFEASIBLE;
    }

    FILE *fp = fopen(FileName, "ra+");
    if (fp == NULL) {
        return ERROR;
    }

    LinkList p = (LNode *)malloc(sizeof(LNode));
    if (p == NULL) {
        return ERROR;
    }
    p->data = 0;
    p->next = NULL;
    L = p;
    while (!feof(fp)) {
        ElemType current_value = 0;
        fread(&current_value, sizeof(ElemType), 1, fp);
        if (!current_value) {
            break;
        }
        LNode *current_node = (LNode *)malloc(sizeof(LNode));
        if (current_node == NULL) {
            return ERROR;
        }
        current_node->data = current_value;
        current_node->next = NULL;
        p->next = current_node;
        p = p->next;
    }

    fclose(fp);
    return OK;
    /********** End 2 **********/
}
