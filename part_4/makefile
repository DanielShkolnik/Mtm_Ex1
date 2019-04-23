eurovision: eurovision.o friendlyStates.o judge.o state.o stateScore.o stateVotes.o eurovisionTests.o eurovisionTestsMain.o test_utilities.o
    gcc eurovision.o friendlyStates.o judge.o state.o stateScore.o stateVotes.o eurovisionTests.o eurovisionTestsMain.o test_utilities.o -o eurovision -l libmtm.a

eurovision.o: eurovision.c eurovision.h
    gcc -c eurovision.c

friendlyStates.o: friendlyStates.c friendlyStates.h
    gcc -c friendlyStates.c

judge.o: judge.c judge.h
    gcc -c judge.c

state.o: state.c state.h
    gcc -c state.c

stateScore.o: stateScore.c stateScore.h
    gcc -c stateScore.c

stateVotes.o: stateVotes.c stateVotes.h
    gcc -c stateVotes.c

eurovisionTests.o: eurovisionTests.c eurovisionTests.h
    gcc -c eurovisionTests.c

eurovisionTestsMain.o: eurovisionTestsMain.c
    gcc -c eurovisionTestsMain.c

test_utilities.o: test_utilities.h
    gcc -c test_utilities.h

