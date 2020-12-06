#include "date.h"
#include "priority_queue.h"
#include "event_manager.h"
#include "events_pq_helper.h"
#include "members_pq_helper.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NULL_INPUT_ERROR -1

struct EventManager_t
{
    Date current_date;
    PriorityQueue events; // each event's date is it's priority,
    // event data = id + name + priority queue of members (priority = id), order by date, then by input time.
    PriorityQueue members; // members - id, name, priority = number of events responsible for (ordered by it)
};
// TODO: Switch params to const?

EventManager createEventManager(Date date)
{
    if (!date)
    {
        return NULL;
    }

    EventManager event_manager = (EventManager)malloc(sizeof(struct EventManager_t));
    if (!event_manager)
    {
        return NULL;
    }

    event_manager->current_date = dateCopy(date);
    event_manager->events = pqCreate(copyEventElement, freeEventElement, equalEventElement, copyEventPriority,
                                     freeEventPriority, compareEventPriorities);
    if (!event_manager->events)
    {
        return NULL;
    }

    event_manager->members = pqCreate(copyMemberElement, freeMemberElement, EqualMemberElement, copyMemberPriority,
                                      freeMemberPriority, CompareMemberPriorities);
    if (!event_manager->members)
    {
        return NULL;
    }

    return event_manager;
}

void destroyEventManager(EventManager em)
{
    dateDestroy(em->current_date);
    pqDestroy(em->events);
    pqDestroy(em->members);
    free(em);
}

EventManagerResult emAddEventByDate(EventManager em, char *event_name, Date date, int event_id)
{
    if (!em || !event_name || !date || event_id)
    {
        return EM_NULL_ARGUMENT;
    }

    // TODO: what to do when equals 0?
    if (dateCompare(em->current_date, date) >= 0)
    {
        return EM_INVALID_DATE;
    }

    if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }

    if (isEventExists(em->events, event_name, date))
    { 
        return EM_EVENT_ALREADY_EXISTS;
    }

    PQElement event = createEventElement(event_name, event_id, date, NULL);
    if (!event)
    { 
        return EM_OUT_OF_MEMORY;
    }

    if (pqContains(em->events, event))
    {
        freeEventElement(event);
        return EM_EVENT_ID_ALREADY_EXISTS;
    }

    PriorityQueueResult result = pqInsert(em->events, event, (PQElementPriority)date);

    freeEventElement(event);

    switch (result)
    {
        case PQ_OUT_OF_MEMORY:
            return EM_OUT_OF_MEMORY;
            
        case PQ_NULL_ARGUMENT:
            return EM_NULL_ARGUMENT;
        
        default:
            return EM_SUCCESS;
    }
}

EventManagerResult emAddEventByDiff(EventManager em, char *event_name, int days, int event_id)
{
    if (!em || !event_name || !days || event_id)
    {
        return EM_NULL_ARGUMENT;
    }

    if (days < 0)
    {
        return EM_INVALID_DATE;
    }

    Date date = dateCopy(em->current_date);
    if (!date)
    {
        return EM_OUT_OF_MEMORY;
    }

    for (int i = 0; i < days; i++)
    {
        dateTick(date);
    }

    return emAddEventByDate(em, event_name, date, event_id);
}

EventManagerResult emRemoveEvent(EventManager em, int event_id)
{
    if (!em || !event_id)
    {
        return EM_NULL_ARGUMENT;
    }

    if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }

    PQElement event = createEventElement(NULL, event_id, NULL, NULL);
    if (!event)
    {
        return EM_OUT_OF_MEMORY;
    }
    
    PriorityQueueResult result = pqRemoveElement(em->events, event);
    
    freeEventElement(event);

    switch (result)
    {
        case PQ_ELEMENT_DOES_NOT_EXISTS:
            return EM_EVENT_NOT_EXISTS;
            
        case PQ_NULL_ARGUMENT:
            return EM_NULL_ARGUMENT;
        
        default:
            return EM_SUCCESS;
    }
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date)
{
    if (!em || !event_id || !new_date)
    {
        return EM_NULL_ARGUMENT;
    }

    if (dateCompare(em->current_date, new_date) >= 0)
    {
        return EM_INVALID_DATE;
    }

    if (event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }

    EventElement event = getEvent(em->events, event_id);
    if (!event)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }

    if (isEventExists(em->events, event->event_name, new_date))
    { 
        return EM_EVENT_ALREADY_EXISTS;
    }

    PriorityQueueResult result = pqChangePriority(em->events, event, event->date, new_date);
    event->date = dateCopy(new_date);
    if(!event->date)
    {
        return EM_OUT_OF_MEMORY;
    }
    
    switch (result)
    {
        case PQ_NULL_ARGUMENT:
            return EM_NULL_ARGUMENT;
        
        case PQ_OUT_OF_MEMORY:
            return EM_OUT_OF_MEMORY;

        case PQ_ELEMENT_DOES_NOT_EXISTS:
            return EM_EVENT_ID_NOT_EXISTS;

        default:
            return EM_SUCCESS;
    }
}

EventManagerResult emTick(EventManager em, int days)
{
    if (!em || !days)
    {
        return EM_NULL_ARGUMENT;
    }

    if (days <= 0)
    {
        return EM_INVALID_DATE;
    }

    EventManagerResult result;
    for (int i = 0; i < days; i++)
    {
        dateTick(em->current_date);
        
        while (dateCompare(((EventElement)pqGetFirst(em->events))->date, em->current_date) <= 0)
        { // remove events
            result = emRemoveEvent(em, ((EventElement)pqGetFirst(em->events))->event_id);
            if (result == EM_OUT_OF_MEMORY)
            {
                return result;
            }
            assert(result == EM_SUCCESS);
        }
    }
    return EM_SUCCESS;
}

int emGetEventsAmount(EventManager em)
{
    if (!em)
    {
        return NULL_INPUT_ERROR;
    }

    return pqGetSize(em->events);
}