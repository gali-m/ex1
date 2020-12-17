CC = gcc
COMP_FLAG = -std=c99 --pedantic-errors -Wall -Werror 
EM_OBJS = tests/event_manager_tests.o event_manager.o date.o events_pq_helper.o members_pq_helper.o pq_helper.o priority_queue.o
PQ_OBJS = tests/priority_queue_tests.o priority_queue.o pq_helper.o

event_manager: $(EM_OBJS) 
	$(CC) $(EM_OBJS) -o $@

priority_queue: $(PQ_OBJS)
	$(CC) $(PQ_OBJS) -o $@



tests/priority_queue_tests.o: priority_queue.h tests/test_utilities.h tests/priority_queue_tests.c
	$(CC) -c $(COMP_FLAG) $*.c -o tests/priority_queue_tests.o

pq_helper.o: pq_helper.c pq_helper.h priority_queue.h
	$(CC) -c $(COMP_FLAG) $*.c

priority_queue.o: priority_queue.c priority_queue.h pq_helper.h
	$(CC) -c $(COMP_FLAG) $*.c




tests/event_manager_tests.o: tests/event_manager_tests.c tests/test_utilities.h event_manager.h date.h
	$(CC) -c $(COMP_FLAG) $*.c -o tests/event_manager_tests.o

event_manager.o: event_manager.c date.h priority_queue.h event_manager.h events_pq_helper.h members_pq_helper.h
	$(CC) -c $(COMP_FLAG) $*.c

date.o: date.c date.h
	$(CC) -c $(COMP_FLAG) $*.c

events_pq_helper.o: events_pq_helper.c date.h priority_queue.h events_pq_helper.h members_pq_helper.h
	$(CC) -c $(COMP_FLAG) $*.c

members_pq_helper.o: members_pq_helper.c date.h priority_queue.h members_pq_helper.h
	$(CC) -c $(COMP_FLAG) $*.c

clean:
	rm -f $(EM_OBJS) $(EM_OBJS) $(EXEC)
