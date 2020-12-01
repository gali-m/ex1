#include "date.h"
#include "priority_queue.h"
#include "event_manager.h"
#include <stdlib.h>
#include <string.h>

struct EventManager_t
{
    Date current_date;
    PriorityQueue events; // each event's date is it's priority, 
    // event data = id + name + priority queue of members (priority = id), order by date, then by input time.
    PriorityQueue members; // members - id, name, priority = number of events responsible for (ordered by it)
};

typedef struct EventElement_t
{
    char* event_name;
    int event_id;
    PriorityQueue members;
} *EventElement;

typedef struct MemberElement_t
{
    char* member_name;
    int member_id;
} *MemberElement;

//TODO: Static funcs for using priority queue: events by date, members by id, members by num of events.
//TODO: create funcs as well.
//TODO: Add members priority queue to event funcs.


// Functions for event members priority queue:

static PQElement copyEventMember(PQElement element)
{
    if (!element) {
        return NULL;
    }

    int* element_copy = (int*)malloc(sizeof(int));
    if (!element_copy) {
        return NULL;
    }

    *element_copy = *(int*)element;

    return (PQElement)element_copy;
}

static void freeEventMember(PQElement element)
{
    free((int*)(element));
}

static bool EqualEventMember(PQElement element1, PQElement element2)
{
    if (!element1 || !element2) {
        return false;
    }

    return ((int*)element1 == (int*)element2);
}

static int CompareEventMemberPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2 || *(int*)priority1 == *(int*)priority2)
    {
        return 0;
    }
    return (*(int*)priority1 < *(int*)priority2) ? 1 : -1;
}

// Functions for events priority queue:

static PQElement createEventElement(char* event_name, int event_id, PriorityQueue members)
{
    EventElement event_element = (EventElement)malloc(sizeof(struct EventElement_t));
    if (!event_element) {
        return NULL;
    }

    event_element->event_id = event_id;
    event_element->members = pqCopy(members);
    event_element->event_name = malloc(strlen(event_name) + 1);
    if (!event_element->event_name) {
        return NULL;
    }

    strcpy(event_element->event_name, event_name);

    return (PQElement)event_element;
}

static PQElement copyEventElement(PQElement element)
{
    if (!element) {
        return NULL;
    }

    PQElement element_copy = createEventElement(((EventElement)(element))->event_name,
                                             ((EventElement)(element))->event_id, ((EventElement)(element))->members);
    if (!element_copy) {
        return NULL;
    }

    return (PQElement)element_copy;
}

static void freeEventElement(PQElement element)
{
    free(((EventElement)(element))->event_name);
    pqDestroy(((EventElement)(element))->members);
    free((EventElement)(element));
}

static PQElementPriority CopyEventPriority(PQElementPriority priority)
{
    if (!priority) {
        return NULL;
    }

    PQElementPriority priority_copy = dateCopy((Date)(priority));
    if (!priority_copy) {
        return NULL;
    }
    return (PQElementPriority)priority_copy;
}

static void FreeEventPriority(PQElementPriority priority)
{
    dateDestroy((Date)priority);
}

static bool EqualEventElement(PQElement element1, PQElement element2)
{
    if (!element1 || !element2) {
        return false;
    }

    return (((EventElement)(element1))->event_id == ((EventElement)(element2))->event_id);
}

static int CompareEventPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2)
    {
        return 0;
    }
    return dateCompare((Date)priority2,(Date)priority1);
}

// Functions for members priority queue:

static PQElement createMemberElement(char* event_name, int event_id, PriorityQueue members)
{
    EventElement event_element = (EventElement)malloc(sizeof(struct EventElement_t));
    if (!event_element) {
        return NULL;
    }

    event_element->event_id = event_id;
    event_element->members = pqCopy(members);
    event_element->event_name = malloc(strlen(event_name) + 1);
    if (!event_element->event_name) {
        return NULL;
    }

    strcpy(event_element->event_name, event_name);

    return (PQElement)event_element;
}

static PQElement copyMemberElement(PQElement element)
{
    if (!element) {
        return NULL;
    }

    PQElement element_copy = createEventElement(((EventElement)(element))->event_name,
                                             ((EventElement)(element))->event_id, ((EventElement)(element))->members);
    if (!element_copy) {
        return NULL;
    }

    return (PQElement)element_copy;
}

static void freeMemberElement(PQElement element)
{
    free(((EventElement)(element))->event_name);
    pqDestroy(((EventElement)(element))->members);
    free((EventElement)(element));
}

static PQElementPriority CopyMemberPriority(PQElementPriority priority)
{
    if (!priority) {
        return NULL;
    }

    PQElementPriority priority_copy = dateCopy((Date)(priority));
    if (!priority_copy) {
        return NULL;
    }
    return (PQElementPriority)priority_copy;
}

static void FreeMemberPriority(PQElementPriority priority)
{
    dateDestroy((Date)priority);
}

static bool EqualMemberElement(PQElement element1, PQElement element2)
{
    if (!element1 || !element2) {
        return false;
    }

    return (((EventElement)(element1))->event_id == ((EventElement)(element2))->event_id);
}

static int CompareMemberPriorities(PQElementPriority priority1, PQElementPriority priority2)
{
    if (!priority1 || !priority2)
    {
        return 0;
    }
    return dateCompare((Date)priority2,(Date)priority1);
}

