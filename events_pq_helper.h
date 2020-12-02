#ifndef EVENTS_PQ_HELPER_H_
#define EVENTS_PQ_HELPER_H_

#include "priority_queue.h"

typedef struct EventElement_t *EventElement;

PQElement copyEventMember(PQElement element);

void freeEventMember(PQElement element);

bool equalEventMember(PQElement element1, PQElement element2);

int compareEventMemberPriorities(PQElementPriority priority1, PQElementPriority priority2);

PQElement createEventElement(char* event_name, int event_id, Date date, PriorityQueue members);

PQElement copyEventElement(PQElement element);

void freeEventElement(PQElement element);

PQElementPriority copyEventPriority(PQElementPriority priority);

void freeEventPriority(PQElementPriority priority);

bool equalEventElement(PQElement element1, PQElement element2);

int compareEventPriorities(PQElementPriority priority1, PQElementPriority priority2);

#endif //EVENTS_PQ_HELPER_H_