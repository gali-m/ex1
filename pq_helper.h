#ifndef PQ_HELPER_H
#define PQ_HELPER_H

#include <stdbool.h>
#include "priority_queue.h"

/** Type for defining the element node */
typedef struct element_t
{
    PQElement element_data;
    PQElementPriority element_priority;
    struct element_t* next;
} *ElementNode;

struct PriorityQueue_t
{
    CopyPQElement copy_element;
    FreePQElement free_element;
    EqualPQElements equal_elements;
    CopyPQElementPriority copy_priority;
    FreePQElementPriority free_priority;
    ComparePQElementPriorities compare_priorities;
    ElementNode element_list;
    ElementNode iterator;
    bool is_iterator_undefined;
};

/**
*   createNewElementNode: Create new element node.
*   allocate new place and initilise the element_data to elemet and the element_priority to priority
*   The next pointer of the new element is NULL
*
* @param queue - The priority queue for the copy functions
* @param element - The element data to copy to the new element node.
* @param priority - The element priority to copy to the new element node.
* @return
* 	NULL if a NULL was sent to the function or if an allocation failed.
* 	ElementNode new_element when the create success.
*/
ElementNode createNewElementNode(PriorityQueue queue, PQElement element, PQElementPriority priority);

/**
*   freeElementNode: Free the element node, include the element_data, element_priority.
*
* @param queue - The priority queue for the copy functions
* @param element - The element data to copy to the new element node.
* 
*/
void freeElementNode(PriorityQueue queue, ElementNode element);

/**
*   removeElementNode: Remove and free element node from the element list of the queue.
*   free the element to remove and connect the element before with the next element.
*
* @param queue - The priority queue for the copy functions
* @param element_before - The element before the element to remove.
* @return
* 	PQ_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	PQ_SUCCESS the element node removed successfully
*/
PriorityQueueResult removeElementNode(PriorityQueue queue, ElementNode element_before);

/**
*   copyElementList: copy element list to new element list.
*   allocate the new element nodes in the new list and copy to them the original element data and priority
*
* @param queue - The priority queue to copy from.
* @return
* 	NULL if a NULL was sent as one of the parameters
* 	ElementNode new_element_list - the new element list that copy
*/
ElementNode copyElementList(PriorityQueue queue);



#endif /* PQ_HELPER_H */