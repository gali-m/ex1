#include "date.h"
#include "priority_queue.h"
#include "event_manager.h"
#include <stdlib.h>
#include <string.h>

struct EventManager_t
{
    Date current_date;
    PriorityQueue events; // each event's date is it's priority, data = id + name +  priority queue of members (priority = id), order by date, then by input time.
    PriorityQueue members; // members - id, name, priority = number of events responsible for (ordered by it)
};

typedef struct event_element_t
{
    char* event_name;
    int event_id;
} *EventElement;

//TODO: Static funcs for using priority queue: events by date, members by id, members by num of events.
//TODO: create funcs as well.


//functions for events priority queue:

static PQElement createEventElement(char* event_name, int event_id)
{
    EventElement event_element = (EventElement)malloc(sizeof(struct event_element_t));
    if (!event_element) {
        return NULL;
    }

    event_element->event_id = event_id;
    event_element->event_name = malloc(strlen(event_name) + 1);
    if (!event_element->event_name) {
        return NULL;
    }
    strcpy(event_element->event_name, event_name);
    return (PQElement)event_element;
}

static PQElement copyEvenetlement(PQElement element)
{
    if (!element) {
        return NULL;
    }
    PQElement element_copy = createEventElement(((EventElement)(element))->event_name, ((EventElement)(element))->event_id);
    if (!element_copy) {
        return NULL;
    }
    return (PQElement)element_copy;
}

static void freeEventElement(PQElement element)
{
    free(((EventElement)(element))->event_name);
    free((EventElement)(element));
}

// static PQElement createEventPriority()
// {
//     EventElement event_element = (EventElement)malloc(sizeof(struct event_element_t));
//     if (!event_element) {
//         return NULL;
//     }

//     event_element->event_id = event_id;
//     event_element->event_name = malloc(strlen(event_name) + 1);
//     if (!event_element->event_name) {
//         return NULL;
//     }
//     strcpy(event_element->event_name, event_name);
//     return (PQElement)event_element;
// }

// /** Type of function for copying a key element of the priority queue */
// static PQElementPriority CopyPQElementPriority(PQElementPriority priority);

// /** Type of function for deallocating a key element of the priority queue */
// static void FreePQElementPriority(PQElementPriority priority);


// /**
// * Type of function used by the priority queue to identify equal elements.
// * This function should return:
// * 		true if they're equal;
// *		false otherwise;
// */
// static bool EqualPQElements(PQElement element1, PQElement element2);


// /**
// * Type of function used by the priority queue to compare priorities.
// * This function should return:
// * 		A positive integer if the first element is greater;
// * 		0 if they're equal;
// *		A negative integer if the second element is greater.
// */
// static int ComparePQElementPriorities(PQElementPriority priority1, PQElementPriority priority2);

