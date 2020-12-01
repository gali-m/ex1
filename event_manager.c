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
