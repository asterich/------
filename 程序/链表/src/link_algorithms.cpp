#include "link_algorithms.h"

void reverse_list(const LinkList& head) {
    if (!head->next) {
        return;
    }

    LNode* tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    if (tail == head->next) {
        return;
    }

    LNode *prev = NULL, *current = head->next, *next = current->next;
    while (next != NULL) {  // TODO: end condition
        current->next = prev;
        prev = current;
        current = next;
        next = current->next;
    }
    current->next = prev;

    head->next = tail;

    return;
}

status reverseList(LinkList& list) {
    if (!list) {
        return INFEASIBLE;
    }
    reverse_list(list);
    return OK;
}

LNode* merge(LNode*& head1, LNode*& head2) {
    LNode* newHead;
    // Base case: return the other half if  one of them is NULL
    if (head1 == NULL)
        return head2;
    else if (head2 == NULL)
        return head1;

    // compare the value
    if (head1->data < head2->data) {
        newHead = head1;  // assign the newHead to the Node has smaller value
        newHead->next = merge(
            head1->next, head2);  // recall the functionto find the next Node
    } else {
        newHead = head2;
        newHead->next = merge(head1, head2->next);
    }

    return newHead;
}

/**
 * @brief Sort a link with mergesort
 *
 * @param head Link to sort
 */
void mergesort(LNode*& head) {
    if (head->next != NULL) {
        LNode* head1 = head;
        LNode* head2 = head;  // assign head to head 2. Head 2 will point to
                              // second half of the linked list
        int len = ListLength(head);
        for (int i = 0; i <= len / 2;
             i++)  // use for loop to increment the pointer 2 to the mid poin in
                   // linked list
        {
            head1 = head2;        // assign head1 to any node head2 point to,
            head2 = head2->next;  // in order to put NULL terminate for the
                                  // first half of the linked list
        }
        if (head1) {
            head1->next = NULL;  // terminate first half of the linked list
            head1 = head;  // reposition head1 to the beginning of linked list,
                           // also the first node of the first half
        }
        mergesort(head1);
        mergesort(head2);
        head = merge(head1, head2);
    }
}

/**
 * @brief Sort a link.
 *
 * @param head
 */
void listSort(LNode*& head) {
    if (head) {
        mergesort(head->next);
    }
    return;
}

/**
 * @brief Remove the nth element counted backwards from link list %L.
 *
 * @param L
 * @param n
 * @return status
 */
status RemoveNthFromEnd(LinkList& L, int n) {
    if (!L) {
        return INFEASIBLE;
    }
    ElemType _;
    status s = ListDelete(L, ListLength(L) - n + 1, _);
    return s;
}