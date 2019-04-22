#ifndef PART_4_STATE_H
#define PART_4_STATE_H
#include "set.h"
#include "stateVotes.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
typedef enum {
    STATE_SUCCESS,
    STATE_OUT_OF_MEMORY,
    STATE_NULL_ARGUMENT,
    STATE_ITEM_ALREADY_EXISTS,
    STATE_ITEM_DOES_NOT_EXIST
} StateResult;
typedef enum{
    VOTE_REMOVE,
    VOTE_ADD
} VoteAddOrRemove;
typedef struct State_t *State;
State stateCreate(int id, const char* name, const char* song);
State stateCopy(State state);
void stateDestroy(State state);
int stateCompare(State state1,State state2);
int stateGetId(State state);
StateResult stateRemoveVotedState(State state, State remove);
StateResult stateAddOrRemoveVote(State state, int voteStateId, VoteAddOrRemove choice);
StateVote stateGetVote(State state, int stateId);
char* stateGetName(State state);
#endif //PART_4_STATE_H
