CC = gcc
OBJS = eurovision.o friendlyStates.o judge.o state.o stateScore.o stateVotes.o test2018.o eurovisionTestsMain.o
EXEC = eurovision
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ -L. -lmtm

eurovision.o: eurovision.c eurovision.h set.h list.h state.h stateVotes.h judge.h stateScore.h friendlyStates.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

friendlyStates.o: friendlyStates.c friendlyStates.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

judge.o: judge.c judge.h set.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

state.o: state.c state.h set.h stateVotes.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

stateScore.o: stateScore.c stateScore.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

stateVotes.o: stateVotes.c stateVotes.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
eurovisionTestsMain.o: tests/eurovisionTestsMain.c tests/eurovisionTests.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tests/eurovisionTestsMain.c
	
test2018.o: tests/test2018.c tests/../list.h tests/../eurovision.h \
 tests/../set.h tests/../list.h tests/eurovisionTests.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tests/test2018.c
	
clean:
	rm -f $(OBJS) $(EXEC)
