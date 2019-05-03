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
/**
 * Creates a new state
 * @param id : state id.
 * @param name : state name
 * @param song : state song
 * @return a new state struct.
 */
State stateCreate(int id, const char* name, const char* song);
/**
 * Copies a state (deep copy).
 * @param state : state to copy.
 * @return a new copy of the given state.
 */
State stateCopy(State state);
/**
 * Destroy a state and free all its allocated memory in the heap.
 * @param state
 */
void stateDestroy(State state);
/**
 * Compares two states by their ids.
 * @param state1
 * @param state2
 * @return positive if state1 id > state2 id
 *         negative of state1 id < state2 id
 *         0 if the ids are equal.
 */
int stateCompare(State state1,State state2);
/**
 * Returns the state id.
 * @param state
 * @return state id.
 */
int stateGetId(State state);
/**
 * Removes all the votes for a state from a given state.
 * @param state : the state who has votes for the remove state.
 * @param remove : removes all of the votes for them from this state.
 * @return
 */
StateResult stateRemoveVotedState(State state, State remove);
/**
 * Adds or remove a vote from this state to another state
 * @param state : the voting state.
 * @param voteStateId : the id of the voted state.
 * @param choice : to add or to remove.
 * @return SUCCESS if no error occurred or NULL_ARGUMENT if one of the prameters were null
 */
StateResult stateAddOrRemoveVote(State state, int voteStateId, VoteAddOrRemove choice);
/**
 * Gets this states name.
 * @param state
 * @return The name of this state.
 */
char* stateGetName(State state);
/**
 * Gets the top 10 voted states in this state ordered from top voted to least voted
 * @param state
 * @return
 */
int* stateGetVotes(State state);

#endif //PART_4_STATE_H
