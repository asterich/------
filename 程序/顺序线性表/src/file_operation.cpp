#include "sq_list.h"

/**
 * @brief Save a list to the file with name %FileName.
 *
 * @param L
 * @param FileName
 * @return status
 */
status SaveList(SqList L, char FileName[]) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    FILE *fp = fopen(FileName, "wa+");
    if (fp == NULL) {
        perror(FileName);
        return ERROR;
    }

    fwrite(&L.length, sizeof(L.length), 1, fp);
    fwrite(&L.listsize, sizeof(L.listsize), 1, fp);
    fwrite(L.elem, sizeof(ElemType), L.length, fp);

    fclose(fp);
    return OK;
}

/**
 * @brief Load data from the file with name %FileName to an uninitalized list.
 *
 * @param L
 * @param FileName
 * @return status
 */
status LoadList(SqList &L, char FileName[]) {
    if (L.elem != NULL) {
        return INFEASIBLE;
    }

    FILE *fp = fopen(FileName, "ra+");
    if (fp == NULL) {
        return ERROR;
    }

    int length = 0, listsize = 0;
    ElemType *elem_ptr = NULL;
    fread(&length, sizeof(length), 1, fp);
    fread(&listsize, sizeof(listsize), 1, fp);
    elem_ptr = (ElemType *)malloc(listsize * sizeof(ElemType));
    if (elem_ptr == NULL) {
        return ERROR;
    }
    L.elem = elem_ptr;
    elem_ptr = NULL;
    L.length = length;
    L.listsize = listsize;
    fread(L.elem, sizeof(ElemType), L.length, fp);

    fclose(fp);
    return OK;
}