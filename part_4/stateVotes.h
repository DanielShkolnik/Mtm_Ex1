#ifndef PART_4_STATEVOTES_H
#define PART_4_STATEVOTES_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct StateVote_t *StateVote;

StateVote stateVoteCreate(int stateId);
StateVote stateVoteCopy(StateVote stateVote);
void stateVoteDestroy(StateVote stateVote);
int stateVoteCompare(StateVote stateVote1,StateVote stateVote2);
#endif //PART_4_STATEVOTES_H
