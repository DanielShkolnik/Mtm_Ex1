CC = gcc
OBJS = eurovision.o friendlyStates.o judge.o state.o stateScore.o stateVotes.o exampleMain.o
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
	
exampleMain.o: exampleMain.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
clean:
	rm -f $(OBJS) $(EXEC)
