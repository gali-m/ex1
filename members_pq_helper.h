#ifndef MEMBERS_PQ_HELPER_H_
#define MEMBERS_PQ_HELPER_H_

#include "priority_queue.h"

// typedef struct MemberElement_t *MemberElement;

// typedef struct MemberPriority_t *MemberPriority;

typedef struct MemberElement_t
{
    char* member_name;
    int member_id;
    int num_of_events;
} *MemberElement;

typedef struct MemberPriority_t
{
    int num_of_events;
    int member_id;
} *MemberPriority;

PQElement createMemberElement(char* member_name, int member_id, int num_of_events);

PQElement copyMemberElement(PQElement element);

void freeMemberElement(PQElement element);

PQElement createMemberPriority(int member_id, int num_of_events);

PQElementPriority copyMemberPriority(PQElementPriority priority);

void freeMemberPriority(PQElementPriority priority);

bool EqualMemberElement(PQElement element1, PQElement element2);

int CompareMemberPriorities(PQElementPriority priority1, PQElementPriority priority2);

MemberElement getMember(PriorityQueue members, int member_id);

PriorityQueueResult AddMemberToQueue(PriorityQueue members,char* member_name, int member_id);

#endif //MEMBERS_PQ_HELPER_H_