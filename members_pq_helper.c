#include "date.h"
#include "priority_queue.h"
#include "members_pq_helper.h"
#include <stdlib.h>
#include <string.h>

struct MemberElement_t
{
    char* member_name;
    int member_id;
    int num_of_events;
};

struct MemberPriority_t
{
    int num_of_events;
    int member_id;
};

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
    free(((MemberElement)(element))->member_name);
    free((MemberElement)(element));
}

PQElementPriority copyMemberPriority(PQElementPriority priority)
{
    if (!priority) {
        return NULL;
    }

    MemberPriority priority_copy = (MemberPriority)malloc(sizeof(struct MemberPriority_t));
    if (!priority_copy) {
        return NULL;
    }

    priority_copy->num_of_events = ((MemberPriority)priority)->num_of_events;
    priority_copy->member_id = ((MemberPriority)priority)->member_id;


    return (PQElementPriority)priority_copy;
}

void freeMemberPriority(PQElementPriority priority)
{
    free(priority);
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
        return (((MemberPriority)priority1)->member_id < ((MemberPriority)priority2)->member_id) ? 1 : -1;
        
    }
    return (((MemberPriority)priority1)->num_of_events > ((MemberPriority)priority2)->num_of_events) ? 1 : -1;
}