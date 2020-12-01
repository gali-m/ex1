#ifndef MEMBERS_PQ_HELPER_H_
#define MEMBERS_PQ_HELPER_H_

#include "priority_queue.h"

typedef struct MemberElement_t *MemberElement;

typedef struct MemberPriority_t *MemberPriority;

PQElement createMemberElement(char* member_name, int member_id, int num_of_events);

PQElement copyMemberElement(PQElement element);

void freeMemberElement(PQElement element);

PQElementPriority copyMemberPriority(PQElementPriority priority);

void freeMemberPriority(PQElementPriority priority);

bool EqualMemberElement(PQElement element1, PQElement element2);

int CompareMemberPriorities(PQElementPriority priority1, PQElementPriority priority2);

#endif //MEMBERS_PQ_HELPER_H_