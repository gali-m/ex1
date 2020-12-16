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

PQElementPriority createMemberPriority(int member_id, int num_of_events);

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

/**
*   getMember: get a member from the members priority queue.
*   The member's identification is by it's id.
*
* @param members - The members priority queue to search for the member in.
* @param member_id - The id of the member.
* @return
* 	NULL if one the parameters is NULL or if there's no member with id = member_id in the priority queue.
* 	PQElement the member from the members priority queue otherwise.
*/
MemberElement getMember(PriorityQueue members, int member_id);

/**
*   AddMemberToQueue: add a member to the members priority queue.
*
* @param members - The members priority queue to add the member to.
* @param member_id - The id of the member.
* @return
*   PQ_NULL_ARGUMENT if a NULL was sent as one of the parameters.
* 	PQ_OUT_OF_MEMORY if an allocation failed.
* 	PQ_SUCCESS the member had been inserted successfully.
*/
PriorityQueueResult AddMemberToQueue(PriorityQueue members,char* member_name, int member_id);

#endif //MEMBERS_PQ_HELPER_H_