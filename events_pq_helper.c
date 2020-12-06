#include "date.h"
#include "priority_queue.h"
#include "events_pq_helper.h"
#include <stdlib.h>
#include <string.h>

// Functions for event members priority queue:

PQElement copyEventMember(PQElement element)
{
    if (!element) {
        return NULL;
    }

    int *element_copy = (int*)malloc(sizeof(int));
    *element_copy = *(int*)element;

    return (PQElement)element_copy;
}

void freeEventMember(PQElement element)
{
    free((element));
}

bool equalEventMember(PQElement element1, PQElement element2)
{
    if (!element1 || !element2) {
        return false;
    }

    return (*(int*)element1 == *(int*)element2);
}

int compareEventMemberPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2 || *(int*)priority1 == *(int*)priority2)
    {
        return 0;
    }
    return (*(int*)priority2 - *(int*)priority1);
}

// Functions for events priority queue:

PQElement createEventElement(char* event_name, int event_id, Date date, PriorityQueue members)
{
    EventElement event_element = (EventElement)malloc(sizeof(struct EventElement_t));
    if (!event_element) {
        return NULL;
    }

    event_element->event_id = event_id;
    event_element->members = pqCopy(members); // if null won't create a pq, will just be set to NULL

    event_element->date = dateCopy(date);
    if (!date)
    {
        return NULL;
    }

    event_element->event_name = malloc(strlen(event_name) + 1);
    if (!event_element->event_name) {
        return NULL;
    }

    strcpy(event_element->event_name, event_name);

    return (PQElement)event_element;
}

PQElement copyEventElement(PQElement element)
{
    if (!element) {
        return NULL;
    }

    PQElement element_copy = createEventElement(((EventElement)(element))->event_name,
    ((EventElement)(element))->event_id, ((EventElement)(element))->date, ((EventElement)(element))->members);
    
    if (!element_copy) 
    {
        return NULL;
    }

    return element_copy;
}

void freeEventElement(PQElement element)
{
    free(((EventElement)(element))->event_name);
    dateDestroy(((EventElement)(element))->date);
    pqDestroy(((EventElement)(element))->members);
    free((EventElement)(element));
}

PQElementPriority copyEventPriority(PQElementPriority priority)
{
    if (!priority) {
        return NULL;
    }

    PQElementPriority priority_copy = dateCopy((Date)(priority));
    if (!priority_copy) {
        return NULL;
    }
    return priority_copy;
}

void freeEventPriority(PQElementPriority priority)
{
    dateDestroy((Date)priority);
}

bool equalEventElement(PQElement element1, PQElement element2)
{
    if (!element1 || !element2) {
        return false;
    }

    return (((EventElement)(element1))->event_id == ((EventElement)(element2))->event_id);
}

bool isEventExists(PriorityQueue queue, char* event_name, Date date)
{
    if (!queue || !event_name || !date)
    {
        return false;
    }

    PQ_FOREACH(EventElement,event,queue)
    {
        if (strcmp(event->event_name, event_name) == 0 
                    && dateCompare(event->date, date) == 0)
        {
            return true;
        }
    }
    return false;
}

int compareEventPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2)
    {
        return 0;
    }
    return dateCompare((Date)priority2,(Date)priority1);
}

EventElement getEvent(PriorityQueue events, int event_id)
{
    if (!events || !event_id)
    {
        return NULL;
    }

    PQ_FOREACH(EventElement,event,events)
    {
        if(event->event_id == event_id)
        {
            return event;
        }
    }

    return NULL;
}