#include "sq_list.h"
/**
 * @brief Initialize a seq list if not.
 *
 * @param L
 * @return status
 */
status InitList(SqList &L) {
    if (L.elem != NULL) {
        return INFEASIBLE;
    }
    ElemType *p_malloc = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (p_malloc == NULL) {
        return ERROR;
    } else {
        L.elem = p_malloc;
        p_malloc = NULL;
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

/**
 * @brief Destroy a list if not initialized.
 *
 * @param L
 * @return status
 */
status DestroyList(SqList &L) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

/**
 * @brief Clear elements in a seq list.
 *
 * @param L
 * @return status
 */
status ClearList(SqList &L) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    memset(L.elem, 0, L.listsize * sizeof(ElemType));
    L.length = 0;
    return OK;
}

/**
 * @brief Check if a list is empty.
 *
 * @param L
 * @return status
 */
status ListEmpty(SqList L) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    if (!L.length) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Return the length of the given seq list %L.
 *
 * @param L Sequence list
 * @return status
 */
status ListLength(SqList L) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    return L.length;
}

/**
 * @brief Traverse the given seq list %L.
 *
 * @param L Sequence list
 * @return status
 */
status ListTraverse(SqList L) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (L.length == 0) {
        return ERROR;
    }
    for (int i = 1; i <= L.length; i++) {
        printf("%d", L.elem[i - 1]);
        if (i < L.length) {
            printf(" ");
        }
    }
    printf("\n");
    return OK;
}

/**
 * @brief Get the Elem object at position %i and assign it to %e.
 *
 * @param L Seq list
 * @param i Position
 * @param e fish
 * @return status
 */
status GetElem(SqList L, int i, ElemType &e) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i < 1 || i > L.length) {
        return ERROR;
    }
    e = L.elem[i - 1];
    return OK;
}

/**
 * @brief Locate the given element %e in seq list %L. If not found, then returns
 * ERROR(0).
 *
 * @param L Sequence list
 * @param e The element to locate
 * @return int
 */
int LocateElem(SqList L, ElemType e) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    int pos = ERROR;
    for (int i = 0; i < L.length; i++) {
        if (e == L.elem[i]) {
            pos = i + 1;
            break;
        }
    }
    return pos;
}

/**
 * @brief Get the previous elem of %e in %L, and then assign it to %pre.
 *
 * @param L Sequence list
 * @param e The target element
 * @param pre Previous element of %e
 * @return status
 */
status PriorElem(SqList L, ElemType e, ElemType &pre) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    int pos = LocateElem(L, e);
    if (pos <= 1) {
        return ERROR;
    }
    pre = L.elem[pos - 2];
    return OK;
}

/**
 * @brief Get the next elem of %e in %L, and then assign it to %next.
 *
 * @param L Sequence list
 * @param e The target element
 * @param next Next element of %e
 * @return status
 */
status NextElem(SqList L, ElemType e, ElemType &next) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    int pos = LocateElem(L, e);
    if (pos == ERROR || pos >= L.length) {
        return ERROR;
    }
    next = L.elem[pos - 1 + 1];
    return OK;
}

/**
 * @brief Insert an element %e at the position %i to the given sequence list %L.
 *
 * @param L Sequence list
 * @param i Position to insert
 * @param e Element to insert
 * @return status
 */
status ListInsert(SqList &L, int i, ElemType e) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i <= 0 || i > L.length + 1) {
        return ERROR;
    }
    ++L.length;
    if (L.length > L.listsize) {
        status s =
            ReallocList(L, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (s == ERROR || s == INFEASIBLE) {
            return s;
        }
        L.listsize += LISTINCREMENT;
    }
    for (int j = L.length; j > i; j--) {
        L.elem[j - 1] = L.elem[j - 2];
    }
    L.elem[i - 1] = e;
    return OK;
}

/**
 * @brief Delete the element at position %i in seq list %L and assign it to %e.
 *
 * @param L Sequence list
 * @param i Position
 * @param e nothing to say
 * @return status
 */
status ListDelete(SqList &L, int i, ElemType &e) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i <= 0 || i > L.length) {
        return ERROR;
    }
    e = L.elem[i - 1];
    for (int j = i + 1; j <= L.length; j++) {
        L.elem[j - 1 - 1] = L.elem[j - 1];
    }
    --L.length;
    return OK;
}