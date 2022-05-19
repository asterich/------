#ifndef __ALGORITHM_HPP_
#define __ALGORITHM_HPP_

#include <random>
#include <unordered_map>
#include <vector>

#include "sq_list.h"

int gen_rand(int l, int r) {
    std::random_device rand_device;

    std::default_random_engine e1(rand_device());
    std::uniform_int_distribution<int> uniform_dist(l, r);
    int mean = uniform_dist(e1);
    return mean;
}

template <typename T, typename Func>
int partition(T arr[], int l, int r, Func cmp) {
    if (l >= r) return -1;
    int pivot = gen_rand(l, r);
    std::swap(arr[pivot], arr[r]);
    int i = l, j = r - 1;
    while (i < j) {
        while (cmp(arr[i], arr[r]) && i < j) i++;
        while (!cmp(arr[j], arr[r]) && i < j) j--;
        std::swap(arr[i], arr[j]);
    }
    int p2 = r;
    for (int k = l; k < r; k++) {
        if (!cmp(arr[k], arr[r])) {
            p2 = k;
            break;
        }
    }
    std::swap(arr[p2], arr[r]);
    return p2;
}

template <typename T, typename Func>
void quicksort(T arr[], int l, int r, Func cmp) {
    if (l >= r) return;
    int p = partition(arr, l, r, cmp);
    quicksort(arr, l, p - 1, cmp);
    quicksort(arr, p + 1, r, cmp);
    return;
}

template <typename T>
int k_subarray(T arr[], int n, T k) {
    std::unordered_map<T, int> sum_map;
    int res = 0;
    T current_sum = 0;
    for (int i = 0; i < n; i++) {
        current_sum += arr[i];
        if (current_sum == k) ++res;
        if (sum_map.find(current_sum - k) != sum_map.end())
            res += sum_map[current_sum - k];
        ++sum_map[current_sum];
    }
    return res;
}

/**
 * @brief return the max partial sum of sequence list %L.
 *
 * @param L The target list
 * @return ElemType
 */
ElemType max_partial_sum(SqList L) {
    if (L.elem == NULL) {
        return 0x7fffffff;
    }
    ElemType res = 0, sum = 0;
    for (int i = 0; i < L.length; i++) {
        sum = std::max(sum + L.elem[i], L.elem[i]);
        res = std::max(res, sum);
    }
    printf("\n");
    return res;
}

/**
 * @brief Sort a list.
 *
 * @param L
 * @return status
 */
status sort_list(SqList &L) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    quicksort(
        L.elem, 0, L.length - 1,
        [](const ElemType &a, const ElemType &b) -> int { return a < b; });
    return OK;
}

/**
 * @brief Return the sum of the subarrays whose elements adds up to %k.
 *
 * @param L Sequence list
 * @param k nothing to say
 * @return int
 */
int k_subarray(SqList &L, ElemType k) {
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    return k_subarray(L.elem, L.length, k);
}

#endif