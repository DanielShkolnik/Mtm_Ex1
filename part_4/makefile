CC = gcc
OBJS = eurovision.o friendlyStates.o judge.o state.o stateScore.o stateVotes.o eurovisionTests.o eurovisionTestsMain.o test_utilities.o
EXEC = eurovision
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror -L. -lmtm

$(EXEC) : $(OBJS)
    $(CC) $(DEBUG_FLAG) $(OBJS) -o $@

eurovision.o: eurovision.c eurovision.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

friendlyStates.o: friendlyStates.c friendlyStates.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

judge.o: judge.c judge.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

state.o: state.c state.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

stateScore.o: stateScore.c stateScore.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

stateVotes.o: stateVotes.c stateVotes.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

eurovisionTests.o: eurovisionTests.c eurovisionTests.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

eurovisionTestsMain.o: eurovisionTestsMain.c
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

test_utilities.o: test_utilities.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
    rm -f $(OBJS) $(EXEC)
