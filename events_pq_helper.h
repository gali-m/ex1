#ifndef EVENTS_PQ_HELPER_H_
#define EVENTS_PQ_HELPER_H_

#include "priority_queue.h"

// type for an event
typedef struct EventElement_t
{
    char* event_name;
    int event_id;
    Date date;
    PriorityQueue members;
} *EventElement;

// Functions for the events priority queue (and the event members priority queue in it):

/**
*   copyEventMember: Create a new copy of an event member (their id).
*
* @param element - The event member id to copy to the new event member.
* @return
* 	NULL if a NULL was sent to the function or if an allocation failed.
* 	PQElement an event member which is the copy of element otherwise.
*/
PQElement copyEventMember(PQElement element);

/**
*   freeEventMember: Free an event member.
*   
* @param element - The event member to be freed.
* 
*/
void freeEventMember(PQElement element);

/**
*   equalEventMember: Check if two event members are the same person.
*   Two members are equal if they share the same id.
*
* @param element1 - The first event member.
* @param element2 - The second event member.
* @return
* 	FALSE if one of the elements is NULL or if the members ids aren't the same.
*   TRUE if the member ids are identical.
*/
bool equalEventMember(PQElement element1, PQElement element2);

/**
*   compareEventMemberPriorities: Compare two event member's priorities.
*   The comparison is based on ids.
*
* @param priority1 - The first event member's priority = id.
* @param priority1 - The second event member's priority = id.
* @return
*   A positive integer if the first id is smaller than the second id.
* 	0 if they're equal or if one of them is NULL.
*	A negative integer if the second id is smaller.
*/
int compareEventMemberPriorities(PQElementPriority priority1, PQElementPriority priority2);

/**
*   createEventElement: Create a new event.
*
* @param event_name - The event's name.
* @param event_id - The event's id.
* @param date - The date the event is on.
* @param members - The priority queue of members which are responsible for the event.
* @return
* 	NULL if an allocation failed.
* 	PQElement an event containing the data provided otherwise.
*/
PQElement createEventElement(char* event_name, int event_id, Date date, PriorityQueue members);

/**
*   copyEventElement: Create a new copy of an event.
*
* @param element - The event's data to copy to the new event.
* @return
* 	NULL if a NULL parameter was sent to the function or if an allocation failed.
* 	PQElement an event which is the copy of element otherwise.
*/
PQElement copyEventElement(PQElement element);

/**
*   freeEventElement: Free an event.
*   
* @param element - The event to be freed.
* 
*/
void freeEventElement(PQElement element);

/**
*   copyEventPriority: Create a new copy of an event priority (it's date).
*
* @param priority - The event's date to copy to the new priority.
* @return
* 	NULL if a NULL was sent to the function or if an allocation failed.
* 	PQElementPriority an event priority (date) which is the copy of priority otherwise.
*/
PQElementPriority copyEventPriority(PQElementPriority priority);

/**
*   freeEventPriority: Free an event priority (date).
*   
* @param element - The event priority (date) to be freed.
* 
*/
void freeEventPriority(PQElementPriority priority);

/**
*   equalEventElement: Check if two events are the same event.
*   Two events are equal if they share the same id.
*
* @param element1 - The first event.
* @param element2 - The second event.
* @return
* 	FALSE if one of the elements is NULL or if the event ids aren't the same.
*   TRUE if the event ids are identical.
*/
bool equalEventElement(PQElement element1, PQElement element2);

/**
*   compareEventPriorities: Compare two event's priorities.
*   The comparison is based on dates.
*
* @param priority1 - The first event's priority = date.
* @param priority1 - The second event's priority = date.
* @return
*   A positive integer if the first date is occurs before than the second date.
* 	0 if they're the same date or if one of them is NULL.
*	A negative integer if the second date occurs first.
*/
int compareEventPriorities(PQElementPriority priority1, PQElementPriority priority2);


// Helper functions for event_manager's events priority queue:

/**
*   isEventExists: Check if the events priority queue already contains an event on a specific date.
*
* @param queue - The events priority queue to check in.
* @param event_name - The name of the event.
* @param date - The date of the event.
* @return
* 	FALSE if one of the parameters is NULL or if there's no event named event_name on event_date.
* 	TRUE if an event named event_name already exists on event_date.
*/
bool isEventExists(PriorityQueue queue, char* event_name, Date date);

/**
*   getEvent: get an event from the events priority queue.
*   The event's identification is by it's id.
*
* @param events - The events priority queue to search for the event in.
* @param event_id - The id of the event.
* @return
* 	NULL if one the parameters is NULL or if there's no event with id = event_id in the priority queue.
* 	EventElement the event from the events priority queue otherwise.
*/
EventElement getEvent(PriorityQueue events, int event_id);

/**
*   getEventMember: get an event member from the event members priority queue.
*   The event member's identification is by it's id.
*
* @param members - The event members priority queue to search for the event member in.
* @param member_id - The id of the event member.
* @return
* 	NULL if one the parameters is NULL or if there's no member with id = member_id in the priority queue.
* 	PQElement the event member from the event members priority queue otherwise.
*/
PQElement getEventMember(PriorityQueue members, int member_id);

/**
*   AddEventMemberToQueue: add an event member to the event members priority queue.
*
* @param members - The event members priority queue to add the event member to.
* @param member_id - The id of the event member.
* @return
*   PQ_NULL_ARGUMENT if a NULL was sent as one of the parameters.
* 	PQ_OUT_OF_MEMORY if an allocation failed.
* 	PQ_SUCCESS the event member had been inserted successfully.
*/
PriorityQueueResult AddEventMemberToQueue(PriorityQueue members, int member_id);

#endif //EVENTS_PQ_HELPER_H_