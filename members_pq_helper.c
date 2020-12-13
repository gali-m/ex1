#include "date.h"
#include "priority_queue.h"
#include "members_pq_helper.h"
#include <stdlib.h>
#include <string.h>

// Functions for members priority queue:

PQElement createMemberElement(char* member_name, int member_id, int num_of_events)
{
    if (!member_name)
    {
        return NULL;
    }

    // create new member
    MemberElement member_element = (MemberElement)malloc(sizeof(struct MemberElement_t));
    if (!member_element) {
        return NULL;
    }

    // assign a copy of the values to the member
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

    // create a copy of the member
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
        if(((MemberElement)(element))->member_name != NULL)
        {
            free(((MemberElement)(element))->member_name);
        }
        free((MemberElement)(element));
    }
}


PQElementPriority createMemberPriority(int member_id, int num_of_events)
{
    MemberPriority member_element = (MemberPriority)malloc(sizeof(struct MemberPriority_t));
    if (!member_element) {
        return NULL;
    }

    member_element->member_id = member_id;
    member_element->num_of_events = num_of_events;

    return (PQElementPriority)member_element;
}

PQElementPriority copyMemberPriority(PQElementPriority priority)
{
    if (!priority) {
        return NULL;
    }

    PQElementPriority priority_copy = createMemberPriority(((MemberPriority)priority)->member_id, 
                                                   ((MemberPriority)priority)->num_of_events);
    if(priority_copy == NULL)
    {
        return NULL;
    }

    return priority_copy;
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

    // TRUE only if the member ids are identical
    return (((MemberElement)(element1))->member_id == ((MemberElement)(element2))->member_id);
}

int CompareMemberPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2)
    {
        return 0;
    }

    if (((MemberPriority)priority1)->num_of_events == ((MemberPriority)priority2)->num_of_events)
    { // same num_of_events
        // positive if id1 is smaller than id2 , 0 if the ids are identical, negative if id2 is smaller than id1
        return ((MemberPriority)priority2)->member_id - ((MemberPriority)priority1)->member_id;
        
    }

    // positive if priority1's num_of_events is bigger than priority2's , 0 if they are identical, negative if smaller
    return ((MemberPriority)priority1)->num_of_events - ((MemberPriority)priority2)->num_of_events;
}

MemberElement getMember(PriorityQueue members, int member_id)
{
    if (!members)
    {
        return NULL;
    }

    PQ_FOREACH(MemberElement,member,members)
    {
        if(member->member_id == member_id)
        {
            return member;
        }
    }

    return NULL;
}

PriorityQueueResult AddMemberToQueue(PriorityQueue members,char* member_name, int member_id)
{
    if (!member_name)
    {
        return PQ_NULL_ARGUMENT;
    }

    PQElement new_member = createMemberElement(member_name, member_id, 0);
    if(new_member == NULL)
    {
        return PQ_OUT_OF_MEMORY;
    }

    PQElement new_member_priority = createMemberPriority(member_id, 0);
    if(new_member_priority == NULL)
    {
        return PQ_OUT_OF_MEMORY;
    }

    PriorityQueueResult pq_insert_result = pqInsert(members, new_member, new_member_priority);

    freeMemberElement(new_member);
    free(new_member_priority);

    return pq_insert_result;
}
