#include "event_manager.h"
#include "date.h"
#include "priority_queue.h"

struct EventManager_t
{
    Date current_date;
    PriorityQueue events; // each event's date is it's priority, data = id + name + members (id, ordered), order by date, then by input time.
    PriorityQueue members; // members - id, name, number of events responsible for (ordered by it)
};
