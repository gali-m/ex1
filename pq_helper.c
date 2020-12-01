#include <stdlib.h>
#include <assert.h>
#include "priority_queue.h"
#include "pq_helper.h"

#define NULL_INPUT_ERROR -1
#define EQUALS_PRIORITY 0

ElementNode createNewElementNode(PriorityQueue queue, PQElement element, PQElementPriority priority)
{
    if (queue == NULL || element == NULL || priority == NULL)
    {
        return NULL;
    }

    ElementNode new_element = (ElementNode)malloc(sizeof(struct element_t));
    if(new_element == NULL)
    {
        return NULL;
    }

    new_element->element_data = queue->copy_element(element);
    new_element->element_priority = queue->copy_priority(priority);
    new_element->next = NULL;

    return new_element;
}

void freeElementNode(PriorityQueue queue, ElementNode element)
{  
    queue->free_element(element->element_data);
    queue->free_priority(element->element_priority);
    free(element);
}

PriorityQueueResult removeElementNode(PriorityQueue queue, ElementNode element_before)
{
    if (queue == NULL || element_before == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    ElementNode element_to_remove = element_before->next;
    ElementNode next_element = element_to_remove->next;

    freeElementNode(queue, element_to_remove);
    element_before->next = next_element;

    return PQ_SUCCESS;
}

ElementNode copyElementList(PriorityQueue queue)
{
    if (queue == NULL || queue->element_list == NULL)
    {
        return NULL;
    }

    ElementNode current_element = queue->element_list;
    ElementNode new_element_list = createNewElementNode(queue,current_element->element_data, 
                                                        current_element->element_priority);;
    ElementNode new_current_element = new_element_list;

    current_element = current_element->next;

    while(current_element != NULL){
        new_current_element->next = createNewElementNode(queue,current_element->element_data, 
                                                         current_element->element_priority);    
        current_element = current_element->next;
        new_current_element = new_current_element->next;
    }

    return new_element_list;
}