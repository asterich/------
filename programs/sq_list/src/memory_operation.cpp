#include "sq_list.h"

/**
 * @brief Realloc a list.
 *
 * @param L The sequence list to be realloc'd
 * @param new_size New size of the list
 * @return status
 */
status ReallocList(SqList &L, size_t new_size) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (realloc(L.elem, new_size) == NULL) {
        return ERROR;
    }
    return OK;
}