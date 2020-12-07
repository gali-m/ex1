#include "date.h"
#include "priority_queue.h"
#include "members_pq_helper.h"
#include <stdlib.h>
#include <string.h>

// Functions for members priority queue:

PQElement createMemberElement(char* member_name, int member_id, int num_of_events)
{
    MemberElement member_element = (MemberElement)malloc(sizeof(struct MemberElement_t));
    if (!member_element) {
        return NULL;
    }

    member_element->member_id = member_id;
    member_element->num_of_events = num_of_events;
    member_element->member_name = malloc(strlen(member_name) + 1);
    if (!member_element->member_name) {
        return NULL;
    }

    strcpy(member_element->member_name, member_name);

    return (PQElement)member_element;
}

PQElement copyMemberElement(PQElement element)
{
    if (!element) {
        return NULL;
    }

    PQElement element_copy = createMemberElement(((MemberElement)(element))->member_name,
                                    ((MemberElement)(element))->member_id,((MemberElement)(element))->num_of_events);
    if (!element_copy) {
        return NULL;
    }

    return element_copy;
}

void freeMemberElement(PQElement element)
{
    if(element != NULL)
    {
        free(((MemberElement)(element))->member_name);
        free((MemberElement)(element));
    }
}


PQElement createMemberPriority(int member_id, int num_of_events)
{
    MemberPriority member_element = (MemberPriority)malloc(sizeof(struct MemberPriority_t));
    if (!member_element) {
        return NULL;
    }

    member_element->member_id = member_id;
    member_element->num_of_events = num_of_events;

    return (PQElement)member_element;
}

PQElementPriority copyMemberPriority(PQElementPriority priority)
{
    if (!priority) {
        return NULL;
    }

    PQElement priority_copy = createMemberPriority(((MemberPriority)priority)->member_id, 
                                                   ((MemberPriority)priority)->num_of_events);
    if(priority_copy == NULL)
    {
        return NULL;
    }

    return (PQElementPriority)priority_copy;
}

void freeMemberPriority(PQElementPriority priority)
{
    if(priority != NULL)
    {
        free(priority);
    }
}

bool EqualMemberElement(PQElement element1, PQElement element2)
{
    if (!element1 || !element2) {
        return false;
    }

    return (((MemberElement)(element1))->member_id == ((MemberElement)(element2))->member_id);
}

int CompareMemberPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2)
    {
        return 0;
    }

    if (((MemberPriority)priority1)->num_of_events == ((MemberPriority)priority2)->num_of_events)
    {
        if (((MemberPriority)priority1)->member_id == ((MemberPriority)priority2)->member_id)
        {
            return 0;
        }
        return ((MemberPriority)priority2)->member_id - ((MemberPriority)priority1)->member_id;
        
    }
    return ((MemberPriority)priority1)->num_of_events - ((MemberPriority)priority2)->num_of_events;
}