#ifndef PART_4_STATESCORE_H
#define PART_4_STATESCORE_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/** Type for defining the StateScore struct */
typedef struct StateScore_t *StateScore;

/** Type used for returning error codes from StateScore functions */
typedef enum {
    STATESCORE_SUCCESS,
    STATESCORE_OUT_OF_MEMORY,
    STATESCORE_NULL_ARGUMENT,
    STATESCORE_ITEM_ALREADY_EXISTS,
    STATESCORE_ITEM_DOES_NOT_EXIST
} StateScoreResult;


/**
 * Allocates a new StateScore.
 * Create StateScore with state id number (int), state name (string), score average by other states (double)
 * judge score average (double) and percent of how to calculate state scores and judge scores (int).
 *
 * @param id = id number of the state
 * @param name = name of the state
 * @param stateVotesAverage = score average by other states
 * @param judgesVotesAverage = judge score average
 * @param audiencePercent = percent of how to calculate state scores and judge scores
 * @return new StateScore pointer with the params inserted
 */
StateScore stateScoreCreate(int id, char* name, double stateVotesAverage, double judgesVotesAverage, int audiencePercent);

/**
 * stateScoreDestroy: Deallocates an existing StateScore.
 * Clears all elements.
 *
 * @param stateScore Target StateScore to be deallocated. If list is NULL nothing will be
 * done.
 *
 * @return
 * STATESCORE_NULL_ARGUMENT if StateScore pointer is NULL
 * STATESCORE_SUCCESS if the StateScore destroyed successfully.
 */
StateScoreResult stateScoreDestroy(StateScore stateScore);

/**
 * Compare 2 StateScore by their id number.
 *
 * @param stateScore1 to compare
 * @param stateScore2 to compare
 * @return int number that is negative if stateScore2 bigger than stateScore1, equals zero
 * if the 2 StateScore id is the same or positive if stateScore1 bigger than stateScore2.
 */
int stateScoreCompare(StateScore stateScore1, StateScore stateScore2);

/**
*Creates a copy of target StateScore.
*
* The new copy will contain all the elements from the source StateScore in the same order
*
* @param stateScore The target stateScore to copy
* @return
* NULL if a NULL was sent or a memory allocation failed.
* A StateScore containing the same elements with same order.
*
 */
StateScore stateScoreCopy(StateScore stateScore);

/**
 * Returns the stateScore name.
 *
 * @param stateScore The StateScore for which to get the name
 * @return The stateScore name from the StateScore inserted
 */
char* stateScoreGetName(StateScore stateScore);





#endif //PART_4_STATESCORE_H
