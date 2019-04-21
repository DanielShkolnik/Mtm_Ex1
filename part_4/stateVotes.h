#ifndef PART_4_STATEVOTES_H
#define PART_4_STATEVOTES_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    STATEVOTE_SUCCESS,
    STATEVOTE_OUT_OF_MEMORY,
    STATEVOTE_NULL_ARGUMENT,
    STATEVOTE_ITEM_ALREADY_EXISTS,
    STATEVOTE_ITEM_DOES_NOT_EXIST
} StatVoteResult;
typedef struct StateVote_t *StateVote;

StateVote stateVoteCreate(int stateId);
StateVote stateVoteCopy(StateVote stateVote);
void stateVoteDestroy(StateVote stateVote);
int stateVoteCompare(StateVote stateVote1,StateVote stateVote2);
StatVoteResult stateVoteAddVote(StateVote vote);
StatVoteResult stateVoteRemoveVote(StateVote vote);
int stateVoteGetId(StateVote vote);
#endif //PART_4_STATEVOTES_H
