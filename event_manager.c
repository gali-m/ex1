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
    // event data = id + name + priority queue of members (priority = id), ordered by date, then by input time.
    PriorityQueue members; // members data - id, name, priority = number of events responsible for
};
// TODO: Switch params to const?

EventManager createEventManager(Date date)
{
    if (!date)
    {
        return NULL;
    }

    // create an event manager
    EventManager event_manager = (EventManager)malloc(sizeof(struct EventManager_t));
    if (!event_manager)
    {
        return NULL;
    }

    // assign date's copy to the event manager
    event_manager->current_date = dateCopy(date);

    // initialize the priority queues
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
    if (!em || !event_name || !date || !event_id)
    {
        return EM_NULL_ARGUMENT;
    }

    // TODO: what to do when equals 0?
    if (dateCompare(em->current_date, date) >= 0)
    { // date is before current date
        return EM_INVALID_DATE;
    }

    if (event_id < 0)
    { // event_id is invalid
        return EM_INVALID_EVENT_ID;
    }

    if (isEventExists(em->events, event_name, date))
    { // an event with the same name already exists on this date
        return EM_EVENT_ALREADY_EXISTS;
    }

    // create an event to insert to the events queue
    PQElement event = createEventElement(event_name, event_id, date, NULL);
    if (!event)
    { 
        return EM_OUT_OF_MEMORY;
    }

    if (pqContains(em->events, event))
    { // an event with the same id already exists
        freeEventElement(event);
        return EM_EVENT_ID_ALREADY_EXISTS;
    }

    // insert a copy of event to events queue
    PriorityQueueResult result = pqInsert(em->events, event, (PQElementPriority)date);

    freeEventElement(event);

    switch (result)
    { // return the correct result
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
    if (!em || !event_name || !days || !event_id)
    {
        return EM_NULL_ARGUMENT;
    }

    if (days < 0)
    { // date is before current date
        return EM_INVALID_DATE;
    }

    // create the event's date from the current date
    Date date = dateCopy(em->current_date);
    if (!date)
    {
        return EM_OUT_OF_MEMORY;
    }

    // reach the event's date
    for (int i = 0; i < days; i++)
    {
        dateTick(date);
    }

    // insert the event and return the insertion's result
    return emAddEventByDate(em, event_name, date, event_id);
}

EventManagerResult emRemoveEvent(EventManager em, int event_id)
{
    if (!em || !event_id)
    {
        return EM_NULL_ARGUMENT;
    }

    if (event_id < 0)
    { // id is invalid
        return EM_INVALID_EVENT_ID;
    }

    // create an event with event_id for pqRemoveElement function
    PQElement event = createEventElement(NULL, event_id, NULL, NULL);
    if (!event)
    {
        return EM_OUT_OF_MEMORY;
    }
    
    // remove the event by it's id
    PriorityQueueResult result = pqRemoveElement(em->events, event);
    
    freeEventElement(event);

    switch (result)
    { // return the correct result
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
    { // date is before current date
        return EM_INVALID_DATE;
    }

    if (event_id < 0)
    { // id is invalid
        return EM_INVALID_EVENT_ID;
    }

    // get the event to update
    EventElement event = getEvent(em->events, event_id);
    if (!event)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }

    if (isEventExists(em->events, event->event_name, new_date))
    { // an event with the same name already exists on this date
        return EM_EVENT_ALREADY_EXISTS;
    }

    //update the event's date (both in data and in priority)
    event->date = dateCopy(new_date);
    PriorityQueueResult result = pqChangePriority(em->events, event, event->date, new_date);
    if(!event->date)
    {
        return EM_OUT_OF_MEMORY;
    }
    
    switch (result)
    { // return the correct result
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
    { // the event manager's date can only move forward
        return EM_INVALID_DATE;
    }

    for (int i = 0; i < days; i++)
    {
        // promote current date
        dateTick(em->current_date);
    }
    
    EventManagerResult result;

    while (dateCompare(((EventElement)pqGetFirst(em->events))->date, em->current_date) <= 0)
    { // remove events which occur before current date
        result = emRemoveEvent(em, ((EventElement)pqGetFirst(em->events))->event_id);
        if (result == EM_OUT_OF_MEMORY)
        {
            return result;
        }

        assert(result == EM_SUCCESS); // only 2 relevant results
    }

    return EM_SUCCESS;
}

int emGetEventsAmount(EventManager em)
{
    if (!em)
    {
        return NULL_INPUT_ERROR;
    }
    
    // get the number of events in events queue
    return pqGetSize(em->events);
}