#ifndef PART_4_FRIENDLYSTATES_H
#define PART_4_FRIENDLYSTATES_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/** Type for defining the FriendlyStates struct */
typedef struct FriendlyStates_t *FriendlyStates;

/** Type used for returning error codes from FriendlyStates functions */
typedef enum {
    FRIENDLYSTATES_SUCCESS,
    FRIENDLYSTATES_OUT_OF_MEMORY,
    FRIENDLYSTATES_NULL_ARGUMENT,
    FRIENDLYSTATES_ITEM_ALREADY_EXISTS,
    FRIENDLYSTATES_ITEM_DOES_NOT_EXIST
} FriendlyStatesResult;

/**
 * Allocates a new FriendlyStates.
 * Create FriendlyStates with state1 name (string) and state2 name (string)
 *
 * @param nameState1 = state1 name
 * @param nameState2 = state2 name
 * @return new FriendlyStates pointer with the params inserted
 */
FriendlyStates friendlyStatesCreate(const char* nameState1, const char* nameState2);

/**
 * friendlyStatesDestroy: Deallocates an existing Judge.
 * Clears all elements.
 *
 * @param friendlyStates Target FriendlyStates to be deallocated. If list is NULL nothing will be
 * done.
 *
 * @return
 * FRIENDLYSTATES_NULL_ARGUMENT if Judge pointer is NULL
 * FRIENDLYSTATES_SUCCESS if the Judge destroyed successfully.
 */
FriendlyStatesResult friendlyStatesDestroy(FriendlyStates friendlyStates);

/**
 * Compare 2 FriendlyStates by their lexicographical order name.
 *
 * @param friendlyStates1 to compare
 * @param friendlyStates2 to compare
 * @return int number that is negative if friendlyStates2 bigger than friendlyStates1, equals zero
 * if the 2 friendlyStates name is the same or positive if friendlyStates1 bigger than friendlyStates2.
 */
int friendlyStatesCompare(FriendlyStates friendlyStates1, FriendlyStates friendlyStates2);

/**
*Creates a copy of target friendlyStates.
*
* The new copy will contain all the elements from the source judge in the same order
*
* @param friendlyStates The target friendlyStates to copy
* @return
* NULL if a NULL was sent or a memory allocation failed.
* A FriendlyStates containing the same elements with same order.
*
 */
FriendlyStates friendlyStatesCopy(FriendlyStates friendlyStates);

/**
 * Returns the friendlyStates state 1 name.
 *
 * @param friendlyStates The FriendlyStates for which to get the name of the first state
 * @return The friendlyStates name of state 1 from the FriendlyStates inserted
 */
char* friendlyStatesGetName1(FriendlyStates friendlyStates);

/**
 * Returns the friendlyStates state 2 name.
 *
 * @param friendlyStates The FriendlyStates for which to get the name of the second state
 * @return The friendlyStates name of state 2 from the FriendlyStates inserted
 */
char* friendlyStatesGetName2(FriendlyStates friendlyStates);


#endif //PART_4_FRIENDLYSTATES_H
