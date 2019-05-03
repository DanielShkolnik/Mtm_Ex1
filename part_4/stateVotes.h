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
/**
 * This struct purpose is to store all the votes to a state for a state.
 * So this struct comes in use in the state struct.
 */
typedef struct StateVote_t *StateVote;
/**
 * creates a state vote.
 * @param stateId: the id of a state to give votes to.
 * @return a new state vote.
 */
StateVote stateVoteCreate(int stateId);
/**
 * Creates a new copy of state vote.
 * @param stateVote
 * @return a new copy of state vote if succedded or null if an error occurred.
 */
StateVote stateVoteCopy(StateVote stateVote);
/**
 * Destry a state vote and free all its alocated data in the heap.
 * @param stateVote too be destroyed
 */
void stateVoteDestroy(StateVote stateVote);
/**
 * Compares state votes by their ids.
 * @param stateVote1
 * @param stateVote2
 * @return positive if stateVote1 id > stateVte2 id.
 *         negative if stateVte1 id < stateVote2 id.
 *         0 if equal.
 */
int stateVoteCompare(StateVote stateVote1,StateVote stateVote2);
/**
 * Adds a vote to a stateVote.
 * @param vote : voted stateVote
 * @return Success if no error else the error which occurred
 */
StatVoteResult stateVoteAddVote(StateVote vote);
/**
 * Removes a vote to a stateVote.
 * @param vote : voted stateVote
 * @return Success if no error else the error which occurred
 */
StatVoteResult stateVoteRemoveVote(StateVote vote);
/**
 * Gets the state id of a stateVote.
 * @param vote : the StateVote
 * @return the id of a stateVote.
 */
int stateVoteGetId(StateVote vote);
/**
 * returns the number of votes a state has
 * @param vote the stateVote
 * @return the number of votes a state has
 */
int stateVoteGetVote(StateVote vote);
#endif //PART_4_STATEVOTES_H
