#include "date.h"
#include "priority_queue.h"
#include "event_manager.h"
#include "events_pq_helper.h"
#include "members_pq_helper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define NULL_INPUT_ERROR -1
#define FILE_MODE "w"

struct EventManager_t
{
    Date current_date;
    PriorityQueue events; // each event's date is it's priority,
    // event data = id + name + priority queue of members (priority = id), ordered by date, then by input time.
    PriorityQueue members; // members data - id, name, priority = number of events responsible for
};
// TODO: Switch params to const?

static EventManagerResult EmResultToPqResult(PriorityQueueResult result)
{
    if(result == PQ_NULL_ARGUMENT)
    {
        return EM_NULL_ARGUMENT;
    }
    if(result == PQ_OUT_OF_MEMORY)
    {
        return EM_OUT_OF_MEMORY;
    }
    if(result == PQ_SUCCESS)
    {
        return EM_SUCCESS;
    }
    if(result == PQ_ELEMENT_DOES_NOT_EXISTS)
    {
        return EM_EVENT_NOT_EXISTS;
    }
    if(result == PQ_NULL_ARGUMENT)
    {
        return EM_NULL_ARGUMENT;
    }

    return EM_ERROR;
}

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
    if(em != NULL)
    {
        if(em->current_date != NULL)
        {
            dateDestroy(em->current_date);
        }
        if(em->events != NULL)
        {
            pqDestroy(em->events);
        }
        if(em->members != NULL)
        {
            pqDestroy(em->members);
        }       
        free(em);
    }
}

EventManagerResult emAddEventByDate(EventManager em, char *event_name, Date date, int event_id)
{
    if (!em || !event_name || !date)
    {
        return EM_NULL_ARGUMENT;
    }

    if (dateCompare(em->current_date, date) > 0)
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


    return EmResultToPqResult(result);
}

EventManagerResult emAddEventByDiff(EventManager em, char *event_name, int days, int event_id)
{
    if (!em || !event_name)
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
    for(int i = 0; i < days; i++)
    {
        dateTick(date);
    }

    // insert the event and return the insertion's result
    return emAddEventByDate(em, event_name, date, event_id);
}

EventManagerResult emRemoveEvent(EventManager em, int event_id)
{
    if (!em)
    {
        return EM_NULL_ARGUMENT;
    }

    if (event_id < 0)
    { // id is invalid
        return EM_INVALID_EVENT_ID;
    }

    PQElement event = getEvent(em->events, event_id);
    if (!event)
    {
        return EM_EVENT_NOT_EXISTS;
    }

    // remove num of events from the memebers in the event
    PQ_FOREACH(MemberElement, event_member, ((EventElement)(event))->members)
    {
        MemberElement member = getMember(em->members, event_member->member_id);
        if (member == NULL)
        {
            // not supposed to happen
            return EM_MEMBER_ID_NOT_EXISTS;
        }

        member->num_of_events--;
    }
    
    PriorityQueueResult result = pqRemoveElement(em->events, event);

    return EmResultToPqResult(result);
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date)
{
    if (!em || !new_date)
    {
        return EM_NULL_ARGUMENT;
    }

    if (dateCompare(em->current_date, new_date) > 0)
    { // date is before current date
        return EM_INVALID_DATE;
    }

    if (event_id < 0)
    { // id is invalid
        return EM_INVALID_EVENT_ID;
    }

    // get the event to update
    EventElement event = copyEventElement(getEvent(em->events, event_id));
    if (!event)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }

    if (isEventExists(em->events, event->event_name, new_date))
    { // an event with the same name already exists on this date
        return EM_EVENT_ALREADY_EXISTS;
    }

    Date old_date = dateCopy(event->date);
    if(!old_date)
    {
        return EM_OUT_OF_MEMORY;
    }

    if(event->date != NULL)
    {
        dateDestroy(event->date);
    }

    event->date = dateCopy(new_date);
    if(!event->date)
    {
        return EM_OUT_OF_MEMORY;
    }

    //update the event's date (both in data and in priority)
    PriorityQueueResult result = pqChangePriority(em->events, event, old_date, new_date);

    if(old_date != NULL)
    {
        dateDestroy(old_date);
    }

    if(event != NULL)
    {
        freeEventElement(event);
    }

    return EmResultToPqResult(result);
}

EventManagerResult emTick(EventManager em, int days)
{
    if (!em)
    {
        return EM_NULL_ARGUMENT;
    }

    if (days <= 0)
    { // the event manager's date can only move forward
        return EM_INVALID_DATE;
    }

    for(int i = 0; i < days; i++)
    {
        // promote current date
        dateTick(em->current_date);
    }
    
    EventManagerResult result;

    if(em->events == NULL)
    {
        return EM_SUCCESS;
    }

    while ((EventElement)pqGetFirst(em->events) != NULL && dateCompare(((EventElement)pqGetFirst(em->events))->date, em->current_date) < 0)
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

static EventManagerResult AddOrRemoveCheckes(EventManager em, int member_id, int event_id)
{
    if(em == NULL)
    {
        return EM_NULL_ARGUMENT;
    }

    if(member_id < 0)
    {
        return EM_INVALID_MEMBER_ID;
    }

    if(event_id < 0)
    {
        return EM_INVALID_EVENT_ID;
    }
    
    return EM_SUCCESS;
}

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id)
{
    if(em == NULL || member_name == NULL)
    {
        return EM_NULL_ARGUMENT;
    }

    if(member_id < 0)
    {
        return EM_INVALID_MEMBER_ID;
    }

    MemberElement em_member = getMember(em->members, member_id);
    if(em_member != NULL)
    {
        return EM_MEMBER_ID_ALREADY_EXISTS;
    }

    PriorityQueueResult add_result = AddMemberToQueue(em->members, member_name, member_id);

    return EmResultToPqResult(add_result);
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id)
{
    EventManagerResult checks_result = AddOrRemoveCheckes(em, member_id, event_id);
    if( checks_result != EM_SUCCESS)
    {
        return checks_result;
    }

    EventElement event_to_add_member = getEvent(em->events, event_id);
    if (event_to_add_member == NULL)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }

    MemberElement em_member = getMember(em->members, member_id);
    if(em_member == NULL)
    {
        return EM_MEMBER_ID_NOT_EXISTS;
    }

    MemberElement event_member =  getMember(event_to_add_member->members, member_id);
    if(event_member != NULL)
    {
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }

    PriorityQueueResult add_result = AddMemberToQueue(event_to_add_member->members, em_member->member_name, member_id);

    if(add_result == PQ_SUCCESS)
    {
        event_member =  getMember(event_to_add_member->members, member_id);
        em_member->num_of_events++;
        event_member->num_of_events++;
    }

    return EmResultToPqResult(add_result);
}

EventManagerResult emRemoveMemberFromEvent(EventManager em, int member_id, int event_id)
{
    EventManagerResult checks_result = AddOrRemoveCheckes(em, member_id, event_id);
    if( checks_result != EM_SUCCESS)
    {
        return checks_result;
    }

    EventElement event_to_remove_member = getEvent(em->events, event_id);
    if (event_to_remove_member == NULL)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }

    MemberElement em_member = getMember(em->members, member_id);
    if(em_member == NULL)
    {
        return EM_MEMBER_ID_NOT_EXISTS;
    }

    MemberElement event_member =  getMember(event_to_remove_member->members, member_id);
    if(event_member == NULL)
    {
        return EM_EVENT_AND_MEMBER_NOT_LINKED;
    }

    PriorityQueueResult remove_result = pqRemoveElement(event_to_remove_member->members, event_member);
    if(remove_result == PQ_SUCCESS)
    {
        em_member->num_of_events--;
        event_member->num_of_events--;
    }

    return EmResultToPqResult(remove_result);
}

char* emGetNextEvent(EventManager em)
{
    if(em == NULL || em->events == NULL || pqGetSize(em->events) == 0)
    {
        return NULL;
    }

    return ((EventElement)pqGetFirst(em->events))->event_name;
}

void emPrintAllEvents(EventManager em, const char* file_name)
{
    if(em == NULL || file_name == NULL)
    {
        return;
    }

    FILE* events_file = fopen(file_name, FILE_MODE);
    if(events_file == NULL)
    {
        return;
    }

    PQ_FOREACH(EventElement,event,em->events)
    {
        int day, month, year;
        if(!dateGet(event->date, &day, &month, &year))
        {
            return;
        }

        fprintf(events_file, "%s,%d.%d.%d", event->event_name, day, month, year);

        PQ_FOREACH(MemberElement,member,event->members)
        {
            fprintf(events_file, ",%s", member->member_name);
        }

        fprintf(events_file, "\n");
    }

    if(events_file != NULL)
    {
        fclose(events_file);
    }
}


void emPrintAllResponsibleMembers(EventManager em, const char* file_name)
{
    if(em == NULL || file_name == NULL)
    {
        return;
    }

    FILE* members_file = fopen(file_name, FILE_MODE);
    if(members_file == NULL)
    {
        return;
    }

    PQ_FOREACH(MemberElement,member,em->members)
    {
        if(member->num_of_events != 0)
        {
            fprintf(members_file, "%s,%d\n", member->member_name, member->num_of_events);
        }
    }

    if(members_file != NULL)
    {
        fclose(members_file);
    }
}
