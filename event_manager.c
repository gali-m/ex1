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