#ifndef EVENTS_PQ_HELPER_H_
#define EVENTS_PQ_HELPER_H_

#include "priority_queue.h"

// typedef struct EventElement_t *EventElement;

typedef struct EventElement_t
{
    char* event_name;
    int event_id;
    Date date;
    PriorityQueue members;
} *EventElement;

PQElement copyEventMember(PQElement element);

void freeEventMember(PQElement element);

bool EqualEventMember(PQElement element1, PQElement element2);

int CompareEventMemberPriorities(PQElementPriority priority1, PQElementPriority priority2);

PQElement createEventElement(char* event_name, int event_id, Date date, PriorityQueue members);

PQElement copyEventElement(PQElement element);

void freeEventElement(PQElement element);

PQElementPriority CopyEventPriority(PQElementPriority priority);

void FreeEventPriority(PQElementPriority priority);

bool EqualEventElement(PQElement element1, PQElement element2);

bool isEventExists(PriorityQueue queue, char* event_name, Date date);

int compareEventPriorities(PQElementPriority priority1, PQElementPriority priority2);

EventElement getEvent(PriorityQueue events, int event_id);

#endif //EVENTS_PQ_HELPER_H_