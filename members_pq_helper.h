#ifndef MEMBERS_PQ_HELPER_H_
#define MEMBERS_PQ_HELPER_H_

#include "priority_queue.h"

// type for a member
typedef struct MemberElement_t
{
    char* member_name;
    int member_id;
    int num_of_events;
} *MemberElement;

// type for a member's priority
typedef struct MemberPriority_t
{
    int num_of_events;
    int member_id;
} *MemberPriority;

// Functions for the members priority queue:

/**
*   createMemberElement: Create a new member.
*
* @param member_name - The member's name.
* @param member_id - The member's id.
* @param num_of_events - The number of events the member is responsible for.
* @return
* 	NULL if an allocation failed.
* 	PQElement an member containing the data provided otherwise.
*/
PQElement createMemberElement(char* member_name, int member_id, int num_of_events);

/**
*   copyMemberElement: Create a new copy of an member.
*
* @param element - The member's data to copy to the new member.
* @return
* 	NULL if a NULL parameter was sent to the function or if an allocation failed.
* 	PQElement an member which is the copy of element otherwise.
*/
PQElement copyMemberElement(PQElement element);

/**
*   freeMemberElement: Free an member.
*   
* @param element - The member to be freed.
* 
*/
void freeMemberElement(PQElement element);

/**
*   copyMemberPriority: Create a new copy of a member's priority.
*
* @param priority - The member's priority to be copied.
* @return
* 	NULL if a NULL was sent to the function or if an allocation failed.
* 	PQElement a member's priority which is the copy of element otherwise.
*/
PQElementPriority copyMemberPriority(PQElementPriority priority);

/**
*   freeMemberPriority: Free a member priority.
*   
* @param element - The member priority to be freed.
* 
*/
void freeMemberPriority(PQElementPriority priority);

/**
*   equalMemberElement: Check if two members are the same.
*   Two members are equal if they share the same id.
*
* @param element1 - The first member.
* @param element2 - The second member.
* @return
* 	FALSE if one of the elements is NULL or if the member ids aren't the same.
*   TRUE if the member ids are identical.
*/
bool EqualMemberElement(PQElement element1, PQElement element2);

/**
*   compareMemberPriorities: Compare two member's priorities.
*   The comparison is based on num_of_events, then member_id.
*
* @param priority1 - The first member's priority.
* @param priority1 - The second member's priority.
* @return
*   A positive integer if priority1's num_of_events is bigger than priority2's, 
                       or if they are equal and the 1st member_id is smaller than the 2nd one's.
* 	0 if they share the same num_of_events and member_id or if one of the parameters is NULL.
*	A negative integer otherwise
*/
int CompareMemberPriorities(PQElementPriority priority1, PQElementPriority priority2);

#endif //MEMBERS_PQ_HELPER_H_