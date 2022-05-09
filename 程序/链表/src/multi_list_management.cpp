#include "multi_list_management.h"

/**
 * @brief Append an initialized list to %Lists.
 *
 * @param Lists Sequence list table
 * @param ListName Sequence list name
 * @return status
 */
status AddList(LISTS &Lists, const char *ListName) {
    if (Lists.length > Lists.listsize || Lists.length < 0) {
        return ERROR;
    }

    LinkList L = NULL;
    status s = InitList(L);
    if (s != OK) {
        return s;
    }

    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length++].L = L;
    return OK;
}

/**
 * @brief Remove the list with %ListName in %Lists.
 *
 * @param Lists Sequence list table
 * @param ListName Sequence list name
 * @return status
 */
status RemoveList(LISTS &Lists, const char *ListName) {
    if (Lists.length <= 0) {
        return ERROR;
    }

    int pos = -1;
    for (int i = 1; i <= Lists.length; i++) {
        if (strcmp(ListName, Lists.elem[i - 1].name) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        return ERROR;
    }

    DestroyList(Lists.elem[pos - 1].L);

    for (int i = pos; i <= Lists.length; i++) {
        Lists.elem[i - 1] = Lists.elem[i];
    }

    Lists.elem[Lists.length - 1].L = NULL;
    strcpy(Lists.elem[Lists.length - 1].name, "");
    --Lists.length;

    return OK;
}

/**
 * @brief Find list with %ListName in %Lists.
 *
 * @param Lists Sequence list table
 * @param ListName Sequence list name
 * @return status
 */
int LocateList(LISTS Lists, const char *ListName) {
    if (Lists.length <= 0) {
        return ERROR;
    }

    int pos = -1;
    for (int i = 1; i <= Lists.length; i++) {
        if (strcmp(ListName, Lists.elem[i - 1].name) == 0) {
            pos = i;
            break;
        }
    }

    return pos;
}