#include "merge_sort.h"
#include <stdlib.h>
// Step 1:
// We write a function that calculates the length of a given linked list.
//
// In: a List lst
// Out: the length of the list
int list_length(List lst) {
    int length = 0;
    while (lst != NULL) {
        length++;
        lst = lst->next;
    }
    return length;
}

// Step 2:
// We now write a function that takes a linked list, and splits it into two
// linked lists of roughly equal size.
// The function should first find the middle element of the input list (or the
// one just before the middle if the list had even length), and set its "next"
// field to NULL, thus chopping the list in half.
// (If the list was of odd size n, then after calling this function the list
// will contain (n+1)/2 items.)
// A pointer to the first of the remaining items is returned as the output
// of this function.
//
// EXAMPLE:
//
//   List tail = split_lists(lst);
//
// the first (n+1)/2 elements of the input list will remain in lst,
// while tail will point to the last (n-1)/2 elements of the input list.
//
// In: A List lst
// Side effect: the list is split in half. If the input list has n elements,
//   after calling this function only the first n/2 (rounded up) should remain.
// Out: a pointer to the *last* n/2 (rounded down) elements of the input list.
//
// HINT:
// - use the function list_length
// - handle the case where the list is empty separately.
List split_list(List lst) {
    int len = list_length(lst);
    int rounded_up = len/2+len%2;
    for (int i=1; i<rounded_up; i++) {
        lst = lst->next;
    }
    List tail = lst->next;
    lst->next = NULL;
    return tail;
}

// Step 3:
// Now, we will write a function that can merge two *sorted* lists into one.
// Note that it will do this by rewiring the "next" fields of the ListNodes,
// rather than by allocating new list nodes. That means that after calling
// this function, the original lists will no longer be valid. The output
// of the function should be a pointer to the first element of the merged
// list.
//
// EXAMPLE:
//
//   List merged = merge_lists(sorted_list1, sorted_list2);
//
// After this, merged points to the result, while sorted_list1 and
// sorted_list2 point to two nodes that have now become part of the merged
// list.
//
// In: two sorted lists, sorted_lst1 and sorted_lst2.
// Out: a single sorted list containing all the elements from
//      both input lists.
// Side effect: since the function changes the "next" field of the
//      original list nodes, the input lists become invalid.
//
// IMPORTANT HINT:
//
// This is the hardest part of the algorithm, so substantial hints on how
// to program this are provided.
//
// 1. Start by declaring an empty list that will eventually hold the result
//    of the merge, and that will be the value returned by the function.
//
//    List result = NULL;
//
// 2. Also declare variable to hold a pointer to the LAST item that was added
//    to the result. It's necessary to keep track of this because we wish to be
//    able to easily add new items to the tail end of the list, without scanning
//    through the entire thing each time.
//
//    List last_item;
//
// 3. Then, WHILE both sorted lists are not empty:
//    - Declare: List smallest_item;
//      Make smallest_item point to the smallest of the two items at the
//      heads of the two sorted lists.
//
//    - If smallest_item came from sorted_list1, then update
//      sorted_list1 = sorted_list1->next, and otherwise update
//      sorted_list2 = sorted_list2->next. This way, we will process all
//      elements of the sorted lists, and in the correct order as well.
//
//    - Then attach smallest_item to the result list.
//      (This should be handled differently if the result list
//      is still empty.)
//
//    - Finally, remember the location of the last attached item by setting
//      last_item = smallest_item;.
//
// 4. Now, at least one of the two sorted_lists has become empty.
//    Simply attach the other one to the last_item and the merge operation is
//    complete.
//
// 5. But, careful! Does your function work properly if one of the input lists
//    is empty? Perhaps add a test to merge_sort_main to check that you got
//    this right.
List merge_lists(List sorted_lst1, List sorted_lst2) {
    // Check whether the lists are empty and exit the function
    if (sorted_lst1 == NULL) {
        return sorted_lst2;
    }
    if (sorted_lst2 == NULL) {
        return sorted_lst1;
    }

    // Both are not empty
    List result = NULL;
    List last_item = NULL;
    while (sorted_lst1 != NULL && sorted_lst2 != NULL) {
        List smallest_item;
        if (sorted_lst1->item <= sorted_lst2->item) {
            smallest_item = sorted_lst1;
            sorted_lst1 = sorted_lst1->next;
        } else {
            smallest_item = sorted_lst2;
            sorted_lst2 = sorted_lst2->next;
        }
        if (last_item == NULL) {
            result = smallest_item;
        } else {
            last_item->next = smallest_item;
        }
        last_item = smallest_item;
    }
    if (sorted_lst1 == NULL) {
        last_item->next = sorted_lst2;
    } else {
        last_item->next = sorted_lst1;
    }
    return result;
}

// Step 4:
// Finally, we're ready to use all these helper functions to merge sort
// an entire list.
// Given an input list, the merge sort function works as follows:
// - If the input list contains 0 or 1 items, the list is already sorted, and
//   no work has to be done.
// - If the list is longer, then first we split it in two halves using
//   split_list.
// - The two halves are then sorted by calling merge_sort recursively.
//   (Remember that writing recursive functions requires a "suspension of
//   disbelief": just pretend that the merge_sort function you're writing
//   does what it's supposed to do.)
// - Finally, the result is obtained by merging the two sorted halves together
//   by calling merge_lists.
//
// In: an unsorted list.
// Side effect: the list is permuted into sorted order.
// Out: a pointer to the first element of the sorted list
List merge_sort(List lst) {
    if (list_length(lst) < 2) {
        return lst;
    }
    List tail = split_list(lst);
    return merge_lists(merge_sort(lst), merge_sort(tail));
}
