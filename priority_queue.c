#include <stdlib.h>
#include <assert.h>
#include "priority_queue.h"
#include "pq_helper.h"

#define NULL_INPUT_ERROR -1
#define EQUALS_PRIORITY 0

PriorityQueue pqCreate(CopyPQElement copy_element,
                       FreePQElement free_element,
                       EqualPQElements equal_elements,
                       CopyPQElementPriority copy_priority,
                       FreePQElementPriority free_priority,
                       ComparePQElementPriorities compare_priorities)
{

    // check if the inputs are null
    if (!copy_element || !free_element || !equal_elements || !copy_priority || !free_priority || !compare_priorities)
    {
        return NULL;
    }

    PriorityQueue new_priority_queue = (PriorityQueue)malloc(sizeof(struct PriorityQueue_t));
    if (new_priority_queue == NULL)
    {
        return NULL;
    }

    new_priority_queue->copy_element = copy_element;
    new_priority_queue->free_element = free_priority;
    new_priority_queue->equal_elements = equal_elements;
    new_priority_queue->copy_priority = copy_priority;
    new_priority_queue->free_priority = free_priority;
    new_priority_queue->compare_priorities = compare_priorities;
    new_priority_queue->element_list = NULL;
    new_priority_queue->iterator = NULL;
    new_priority_queue->is_iterator_undefined=false;

    return new_priority_queue;

}

void pqDestroy(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return;
    }

    if(queue->element_list == NULL)
    {
        free(queue);
        return;
    }

    while(queue->element_list->next != NULL)
    {  
        removeElementNode(queue, queue->element_list);
    }
    // free last element node
    freeElementNode(queue, queue->element_list);

    free(queue);
}

PriorityQueue pqCopy(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return NULL;
    }

    PriorityQueue new_priority_queue = pqCreate(queue->copy_element, queue->free_element, queue->equal_elements, 
                                  queue->copy_priority, queue->free_priority, queue->compare_priorities);
    if(new_priority_queue == NULL)
    {
        return NULL;
    }

    new_priority_queue->element_list = copyElementList(queue);
    
    new_priority_queue->is_iterator_undefined = true;
    queue->is_iterator_undefined = true;

    return new_priority_queue;
}

int pqGetSize(PriorityQueue queue)
{   
    if (queue == NULL)
    {
        return NULL_INPUT_ERROR;
    }

    int elements_size = 0;

    ElementNode current_element = queue->element_list;

    while(current_element != NULL){
        elements_size++;
        current_element = current_element->next;
    }

    return elements_size;
}

bool pqContains(PriorityQueue queue, PQElement element)
{
    if (queue == NULL || element == NULL)
    {
        return false;
    }

    ElementNode current_element = queue->element_list;

    while(current_element != NULL){

        if(queue->equal_elements(current_element->element_data, element))
        {
            return true;
        }

        current_element = current_element->next;
    }

    return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority)
{
    if (queue == NULL || element == NULL || priority == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    ElementNode new_element = createNewElementNode(queue, element, priority);
    if (new_element == NULL)
    {
        return PQ_OUT_OF_MEMORY;
    }

    queue->is_iterator_undefined = true;

    ElementNode current_element = queue->element_list;
    
    // check if need to be in the first place - the highest priority
    if(current_element == NULL || 
       queue->compare_priorities(current_element->element_priority,new_element->element_priority) < EQUALS_PRIORITY)
    {
        new_element->next = current_element;
        queue->element_list = new_element;
        return PQ_SUCCESS;
    }

    // put the element in the right place in list
    while (current_element->next != NULL)
    {   
        if(queue->compare_priorities(current_element->next->element_priority,
                                     new_element->element_priority) < EQUALS_PRIORITY)
        {
            new_element->next = current_element->next;
            current_element->next = new_element;
            return PQ_SUCCESS;
        }

        current_element = current_element->next;
    }

    // last element in the list
    new_element->next = NULL;
    current_element->next = new_element;
    return PQ_SUCCESS;
}

PriorityQueueResult pqChangePriority(PriorityQueue queue, PQElement element, 
                                     PQElementPriority old_priority, PQElementPriority new_priority)
{
    if (queue == NULL || element == NULL || old_priority == NULL || new_priority == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    queue->is_iterator_undefined = true;

    if(queue->element_list == NULL)
    {
        return PQ_ELEMENT_DOES_NOT_EXISTS;
    }

    ElementNode current_element = queue->element_list;

    // check if the first element is the one that need to change
    if(queue->equal_elements(current_element->element_data, element) &&
        queue->compare_priorities(current_element->element_priority, old_priority) == EQUALS_PRIORITY)
    {
        pqRemove(queue);
        return pqInsert(queue, element, new_priority);
    }

    // remove the element with the old priority and pqInsert with new_priority
    while(current_element->next != NULL){

        if(queue->equal_elements(current_element->next->element_data, element) &&
            queue->compare_priorities(current_element->next->element_priority, old_priority) == EQUALS_PRIORITY)
        {
            removeElementNode(queue, current_element);
            return pqInsert(queue, element, new_priority);    
        }

        current_element = current_element->next;
    }

    return PQ_ELEMENT_DOES_NOT_EXISTS;
}

PriorityQueueResult pqRemove(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    queue->is_iterator_undefined = true;

    if(queue->element_list == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    ElementNode next_element = queue->element_list->next;

    freeElementNode(queue, queue->element_list);
    queue->element_list = next_element;

    return PQ_SUCCESS;

}

PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element)
{
    if (queue == NULL || element == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    queue->is_iterator_undefined = true;
    ElementNode current_element = queue->element_list;
    
    // check if the first element is the one that need to remove
    if(queue->equal_elements(current_element->element_data, element))
    {
        return pqRemove(queue);
    }

    while(current_element->next != NULL){

        if(queue->equal_elements(current_element->next->element_data, element))
        {
            return removeElementNode(queue, current_element);
        }

        current_element = current_element->next;
    }

    return PQ_ELEMENT_DOES_NOT_EXISTS;

}


PriorityQueueResult pqClear(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    while(queue->element_list != NULL)
    {
        pqRemove(queue);
    }

    return PQ_SUCCESS;

}


PQElement pqGetFirst(PriorityQueue queue)
{
    if (queue == NULL || queue->element_list == NULL)
    {
        return NULL;
    }

    queue->iterator = queue->element_list;
    queue->is_iterator_undefined = false;
    return queue->iterator->element_data;
}

PQElement pqGetNext(PriorityQueue queue)
{
    if (queue == NULL || queue->iterator == NULL || queue->is_iterator_undefined || queue->iterator->next == NULL)
    {
        return NULL;
    }

    queue->iterator = queue->iterator->next;
    return queue->iterator->element_data;
}
