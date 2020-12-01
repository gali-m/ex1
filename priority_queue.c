#include <stdlib.h>
#include <assert.h>
#include "priority_queue.h"

#define NULL_INPUT_ERROR -1
#define EQUALS_PRIORITY 0

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
    if (!new_priority_queue)
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
    if (queue != NULL || queue->element_list != NULL)
    {
        return;
    }

    while(queue->element_list != NULL)
    {  
        ElementNode tmp_element = queue->element_list;
        queue->element_list = queue->element_list->next;

        if (tmp_element != NULL)
        {
            queue->free_element(tmp_element->element_data);
            queue->free_priority(tmp_element->element_priority);
            free(tmp_element);
        }
    }
    free(queue);
}

static ElementNode copyElementList(ElementNode element_list, CopyPQElement copy_element, 
                                   CopyPQElementPriority copy_priority)
{
    if (element_list == NULL)
    {
        return NULL;
    }

    ElementNode new_element_list = (ElementNode)malloc(sizeof(struct element_t));
    if (!new_element_list)
    {
        return NULL;
    }

    ElementNode tmp_list = new_element_list;
    tmp_list->element_data = copy_element(element_list->element_data);
    tmp_list->element_priority = copy_priority(element_list->element_priority);

    while(element_list->next != NULL)
    {
        tmp_list->next = (ElementNode)malloc(sizeof(struct element_t));
        if (tmp_list->next == NULL)
        {
            return NULL;
        }

        tmp_list = tmp_list->next;
        element_list = element_list->next;
        tmp_list->element_data = copy_element(element_list->element_data);
        tmp_list->element_priority = copy_priority(element_list->element_priority);
    }
    tmp_list->next = NULL;
    return new_element_list;
}

PriorityQueue pqCopy(PriorityQueue queue)
{
    if (queue == NULL)
    {
        return NULL;
    }

    PriorityQueue new_priority_queue = (PriorityQueue)malloc(sizeof(struct PriorityQueue_t));
    if (!new_priority_queue)
    {
        return NULL;
    }

    new_priority_queue = pqCreate(queue->copy_element, queue->free_element, queue->equal_elements, 
                                  queue->copy_priority, queue->free_priority, queue->compare_priorities);
    if(new_priority_queue == NULL)
    {
        return NULL;
    }
    
    new_priority_queue->element_list = copyElementList(queue->element_list, new_priority_queue->copy_element,
                                                        queue->copy_priority);
    
    new_priority_queue->is_iterator_undefined = true;

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

static ElementNode createNewElementNode(PriorityQueue queue, PQElement element, PQElementPriority priority)
{
    ElementNode new_element = (ElementNode)malloc(sizeof(struct element_t));
    if(new_element == NULL)
    {
        return NULL;
    }

    new_element->element_data = queue->copy_element(element);
    new_element->element_priority = queue->copy_priority(priority);

    return new_element;
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

    // check if need to be in the first place - the highest priority
    if(queue->element_list == NULL || 
       queue->compare_priorities(queue->element_list->element_priority,new_element->element_priority) <= EQUALS_PRIORITY)
    {
        new_element->next = queue->element_list;
        queue->element_list = new_element;
        return PQ_SUCCESS;
    }

    ElementNode current_element = queue->element_list;

    // put the element in the right place in list
    while (current_element->next != NULL)
    {   
        if(queue->compare_priorities(current_element->next->element_priority,
                                     new_element->element_priority) <= EQUALS_PRIORITY)
        {
            new_element->next = current_element->next;
            current_element->next = new_element;
            return PQ_SUCCESS;
        }

        current_element = current_element->next;
    }

    // last element in the list
    new_element->next = NULL;
    current_element = new_element;
    return PQ_SUCCESS;
}

static void freeElementNode(PriorityQueue queue, ElementNode element)
{  
    queue->free_element(element->element_data);
    queue->free_priority(element->element_priority);
    free(element);
}

static PriorityQueueResult removeElementNode(PriorityQueue queue, ElementNode element_before)
{
    ElementNode element_to_remove = element_before->next;
    ElementNode next_element = element_to_remove->next;

    freeElementNode(queue, element_to_remove);
    element_before->next = next_element;

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
        if(queue->compare_priorities(old_priority, new_priority) == EQUALS_PRIORITY)
        {
            return PQ_SUCCESS;
        }

        pqRemove(queue);
        return pqInsert(queue, element, new_priority);
    }

    // remove the element with the old priority and pqInsert with new_priority
    while(current_element->next != NULL){

        if(queue->equal_elements(current_element->next->element_data, element) &&
            queue->compare_priorities(current_element->next->element_priority, old_priority) == EQUALS_PRIORITY)
        {
            if(queue->compare_priorities(old_priority, new_priority) == EQUALS_PRIORITY)
            {
                return PQ_SUCCESS;
            }

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
        // TODO: NULL or SECCESS ?!?!
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
    if (queue == NULL || queue->iterator || queue->is_iterator_undefined)
    {
        return NULL;
    }

    queue->iterator = queue->iterator->next;
    return queue->iterator->element_data;
}
