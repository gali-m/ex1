#include "date.h"
#include "priority_queue.h"
#include "event_manager.h"
#include "events_pq_helper.h"
#include "members_pq_helper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FILE_MODE "w"

struct EventManager_t
{
    Date current_date;
    PriorityQueue events; // each event's date is it's priority, 
    // event data = id + name + priority queue of members (priority = id), order by date, then by input time.
    PriorityQueue members; // members - id, name, priority = number of events responsible for (ordered by it)
};

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

    PQ_FOREACH(MemberElement,member,em->members)
    {
        if (member->member_id == member_id)
        {
            return EM_MEMBER_ID_ALREADY_EXISTS;
        }
    }

    PriorityQueueResult add_result = AddMemberToQueue(em->members, member_name, member_id);

    return EmResultToPqResult(add_result);
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id)
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

    EventElement event_to_add_member = getEvent(em->events, event_id);
    if (event_to_add_member == NULL)
    {
        return EM_EVENT_NOT_EXISTS;
    }

    MemberElement em_member = getMember(em->members, member_id);
    if(em_member == NULL)
    {
        return EM_MEMBER_ID_NOT_EXISTS;
    }

    MemberElement event_member =  getMember(event_to_add_member->members, member_id);
    if(event_member == NULL)
    {
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }

    PriorityQueueResult add_result = AddMemberToQueue(event_to_add_member->members, em_member->member_name, member_id);

    if(add_result == PQ_SUCCESS)
    {
        em_member->num_of_events++;
        event_member->num_of_events++;
    }

    return EmResultToPqResult(add_result);
}

char* emGetNextEvent(EventManager em)
{
    if(em == NULL)
    {
        return NULL;
    }

    return pqGetFirst(em->events);
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

    EventElement current_event = (EventElement)pqGetFirst(em->events);

    while(current_event != NULL)
    {
        // TODO: check who to print date
        fprintf(events_file, "%s,%s", current_event->event_name, current_event->date);

        MemberElement current_member = (MemberElement)pqGetFirst(current_event->members);

        while(current_member != NULL)
        {
            fprintf(events_file, ",%s", current_member->member_name);
        }

        fprintf(events_file, "\n");

        current_event = pqGetNext(em->events);
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

    MemberElement current_member = (MemberElement)pqGetFirst(em->members);

    while(current_member != NULL)
    {
        fprintf(members_file, "%s,%d\n", current_member->member_name, current_member->num_of_events);

        current_member = pqGetNext(em->members);
    }

    if(members_file != NULL)
    {
        fclose(members_file);
    }
}