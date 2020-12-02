#include "date.h"
#include "priority_queue.h"
#include "event_manager.h"
#include "events_pq_helper.h"
#include "members_pq_helper.h"
#include <stdlib.h>
#include <string.h>

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
                                        freeEventPriority,compareEventPriorities);
    if (!event_manager->events)
    {
        return NULL;
    }

    event_manager->members = pqCreate(copyMemberElement,freeMemberElement,EqualMemberElement, copyMemberPriority, 
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

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id)
{
    if (!em || !event_name || !date ||event_id)
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

    PQElement event = createEventElement(event_name, event_id, date, NULL);
    if (!event)
    { // TODO
    // freeEventElement(event); ?
        return EM_OUT_OF_MEMORY;
    }

    if (pqContains(em->events, event))
    {
        freeEventElement(event);
        return EM_EVENT_ID_ALREADY_EXISTS;
    }

    if (0 == 0)
    {// TODO
        freeEventElement(event);
        return EM_EVENT_ALREADY_EXISTS;
    }

    //result pqInsert(em->events, event, (PQElementPriority)date);
    if ()
    return EM_SUCCESS;
}

EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id);

EventManagerResult emRemoveEvent(EventManager em, int event_id);

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date);

EventManagerResult emTick(EventManager em, int days);

int emGetEventsAmount(EventManager em);