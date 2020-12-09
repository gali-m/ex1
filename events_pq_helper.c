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

    // create a new member
    int *element_copy = (int*)malloc(sizeof(int));
    if (!element_copy)
    {
        return NULL;
    }
    
    // copy the member's id
    *element_copy = *(int*)element;

    return (PQElement)element_copy;
}

void freeEventMember(PQElement element)
{
    if(element != NULL)
    {
        free((element));
    }
}

bool equalEventMember(PQElement element1, PQElement element2)
{
    if (!element1 || !element2) {
        return false;
    }

    // TRUE only if the member ids are identical
    return (*(int*)element1 == *(int*)element2);
}

int compareEventMemberPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2)
    {
        return 0;
    }

    // positive if id2 is bigger, 0 if equal, negative if id1 bigger
    return (*(int*)priority2 - *(int*)priority1);
}

// Functions for events priority queue:

PQElement createEventElement(char* event_name, int event_id, Date date, PriorityQueue members)
{
    if(!event_name || !date)
    {
        return NULL;
    }

    // create new event
    EventElement event_element = (EventElement)malloc(sizeof(struct EventElement_t));
    if (!event_element) {
        return NULL;
    }

    // assign a copy of the values to the event
    event_element->event_id = event_id;

    if (members)
    { // the event has members
        event_element->members = pqCopy(members); 
        if (!event_element->members)
        {
            return NULL;
        }
    }
    else
    {
        event_element->members = NULL;
    }
    
    event_element->date = dateCopy(date);
    if (!date)
    {
        return NULL;
    }

    event_element->event_name = (char *)malloc(strlen(event_name) + 1);
    if (!event_element->event_name) {
        return NULL;
    }

    strcpy(event_element->event_name, event_name);

    event_element->members = pqCreate(copyEventMember, freeEventMember, equalEventMember, copyEventMember, 
                                      freeEventMember, compareEventMemberPriorities);
    if(!event_element->members)
    {
        return NULL;
    }
    
    return (PQElement)event_element;
}

PQElement copyEventElement(PQElement element)
{
    if (!element) {
        return NULL;
    }

    // create a copy of the event
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
    if (element != NULL)
    {
        if (((EventElement)(element))->event_name != NULL)
        {
            free(((EventElement)(element))->event_name);
        }
        if (((EventElement)(element))->date != NULL)
        {
            dateDestroy(((EventElement)(element))->date);
        }
        if (((EventElement)(element))->members != NULL)
        {
            pqDestroy(((EventElement)(element))->members);
        }
        free((EventElement)(element));
    }   
}

PQElementPriority copyEventPriority(PQElementPriority priority)
{
    if (!priority) {
        return NULL;
    }

    // create a copy of date
    PQElementPriority priority_copy = dateCopy((Date)(priority));
    if (!priority_copy) {
        return NULL;
    }
    return priority_copy;
}

void freeEventPriority(PQElementPriority priority)
{
    if (priority != NULL)
    {
        dateDestroy((Date)priority);
    }
}

bool equalEventElement(PQElement element1, PQElement element2)
{
    if (!element1 || !element2) {
        return false;
    }

    // TRUE only if the event ids are identical
    return (((EventElement)(element1))->event_id == ((EventElement)(element2))->event_id);
}

int compareEventPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2)
    {
        return 0;
    }

    // positive if date1 is before date2, 0 if the dates are identical, negative if date2 is before date1
    return dateCompare((Date)priority2,(Date)priority1);
}

// Helper functions for events queue in event_manager:

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
        { // TRUE only if an event with the same name and event is found in the event's queue
            return true;
        }
    }

    // no such event was found
    return false;
}

EventElement getEvent(PriorityQueue events, int event_id)
{
    if (!events)
    {
        return NULL;
    }

    PQ_FOREACH(EventElement,event,events)
    {
        if(event->event_id == event_id)
        { // the event was found
            return event;
        }
    }

    // no such event in events
    return NULL;
}