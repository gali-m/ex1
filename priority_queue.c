#include <stdlib.h>
#include <assert.h>
#include "priority_queue.h"

#define NULL_INPUT_ERROR -1

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

    PriorityQueue new_priority_queue = (PriorityQueue)malloc(sizeof(PriorityQueue));
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

static ElementNode copyElementList(ElementNode element_list, CopyPQElement copy_element, CopyPQElementPriority copy_priority)
{
    if (element_list == NULL)
    {
        return NULL;
    }

    ElementNode new_element_list = (ElementNode)malloc(sizeof(ElementNode));
    if (!new_element_list)
    {
        return NULL;
    }

    ElementNode tmp_list = new_element_list;
    tmp_list->element_data = copy_element(element_list->element_data);
    tmp_list->element_priority = copy_priority(element_list->element_priority);

    while(element_list->next != NULL)
    {
        tmp_list->next = (ElementNode)malloc(sizeof(ElementNode));
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

    PriorityQueue new_priority_queue = (PriorityQueue)malloc(sizeof(PriorityQueue));
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

    return new_priority_queue;
}

int pqGetSize(PriorityQueue queue)
{   
    if (queue == NULL)
    {
        return NULL_INPUT_ERROR;
    }

    int elements_size = 0;

    while(queue->element_list != NULL){
        elements_size++;
        queue->element_list = queue->element_list->next;
    }

    return elements_size;

}

bool pqContains(PriorityQueue queue, PQElement element)
{
    if (queue == NULL || element == NULL)
    {
        return false;
    }

    while(queue->element_list != NULL){

        if(queue->equal_elements(queue->element_list->element_data, element))
        {
            return true;
        }

        queue->element_list = queue->element_list->next;
    }

    return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority)
{
    if (queue == NULL || element == NULL || priority == NULL)
    {
        return PQ_NULL_ARGUMENT;
    }

    // create new element
    ElementNode new_element = (ElementNode)malloc(sizeof(ElementNode));
    if(new_element == NULL)
    {
        return PQ_OUT_OF_MEMORY;
    }

    new_element->element_data = queue->copy_element(element);
    new_element->element_priority = queue->copy_priority(priority);

    // check if need to be in the first place - the highest priority
    if(queue->element_list == NULL || queue->element_list->element_priority <= new_element->element_priority)
    {
        new_element->next = queue->element_list;
        queue->element_list = new_element;
        return PQ_SUCCESS;
    }

    // put the element in the right place in list
    while (queue->element_list->next != NULL)
    {        
        if(queue->element_list->next->element_priority <= new_element->element_priority)
        {
            new_element->next = queue->element_list->next;
            queue->element_list->next = new_element;
            return PQ_SUCCESS;
        }

        queue->element_list = queue->element_list->next;
    }

    // last element in the list
    new_element->next = NULL;
    queue->element_list->next = new_element;
    return PQ_SUCCESS;
}

